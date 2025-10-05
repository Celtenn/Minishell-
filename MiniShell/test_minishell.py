#!/usr/bin/env python3

import subprocess
import difflib
import os
import shutil
import re

# =================================================================
# AYARLAR
# =================================================================
MINISHELL_PATH = './minishell'
VALGRIND_PATH = shutil.which('valgrind')
ERROR_FILE = 'Errors1.txt'
# readline.supp dosyası, readline kütüphanesinin bilinen bellek sızıntılarını
# valgrind'in görmezden gelmesini sağlar. Proje dizininizde oluşturun.
SUPPRESSIONS_FILE = 'readline.supp'

# =================================================================
# TEST SENARYOLARI
# =================================================================
TEST_CASES = [
    # 1. BUILT-IN KOMUTLAR
    'echo hello world',
    'echo "hello   world"',
    'cd / && pwd',
    'pwd && export OLDPWD=$(pwd) && cd /tmp && cd - && pwd',
    'pwd',
    'export VAR=hello && echo $VAR',
    'export NOEQUAL',
    'export VAR_TO_UNSET=1 && unset VAR_TO_UNSET && echo $VAR_TO_UNSET',
    'exit 42',

    # 2. ENVIRONMENT VE EXPAND
    'export X=world && echo hello $X',
    'ls non_existent_file_123 ; echo $?',
    'echo $UNDEF_VAR_123',

    # 3. REDIRECTIONS
    'echo hello > out.txt && cat out.txt',
    'echo line1 > out.txt && echo line2 >> out.txt && cat out.txt',
    'echo content > out.txt && cat < out.txt',

    # 4. HEREDOC
    'cat << EOF\nhello\nEOF',
    'export A=hi && cat << EOF\n$A\nEOF',
    'export A=hi && cat << "EOF"\n$A\nEOF',
    # 'cat << EOF\n^C' # Sinyal testi, manuel olarak yapılmalı

    # 5. PIPE
    'echo hello | cat',
    'echo hello | cat | cat',
    'echo hello | cat > out.txt && cat out.txt',

    # 6. SYNTAX HATALARI
    '',
    '   ',
    'echo "hello',
    'echo hello |',
    'cat <<',
    'cat >',

    # 7. KARMA KOMUTLAR
    'export X=bye && cat << EOF | grep $X\nhello\nbye\nEOF',
    'cat << EOF > out.txt\nhello\nEOF && cat out.txt',
    'cat << "END"\n$USER\nEND',
    'cat << EOF | cat\nhello\nEOF',

    # 8. SİNYAL TESTLERİ (Manuel)
    # Prompt'ta Ctrl-C
    # Heredoc'ta Ctrl-C
]

# Temizleme için kullanılacak dosyalar
CLEANUP_FILES = [
    'out.txt', 'out2.txt', 'out3.txt', 'ls_out.txt', 'no_nl.txt',
    'cmd_not_found.txt', 'test2.txt', 'final.txt', 'file', 'file1', 'file2', 'f1', 'f2'
]

def run_shell(command, shell='/bin/bash'):
    """Verilen komutu belirtilen shell'de çalıştırır."""
    return subprocess.run(
        [shell, '-c', command],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        timeout=5  # Sonsuz döngüleri yakalamak için
    )

def run_minishell(command):
    """Minishell'i valgrind ile çalıştırır."""
    if not VALGRIND_PATH:
        raise RuntimeError("valgrind bulunamadı. Lütfen yükleyin.")

    valgrind_command = [
        VALGRIND_PATH,
        '--leak-check=full',
        '--show-leak-kinds=all',
        '--error-exitcode=42',
        MINISHELL_PATH
    ]
    if os.path.exists(SUPPRESSIONS_FILE):
        valgrind_command.insert(4, f'--suppressions={SUPPRESSIONS_FILE}')

    # Heredoc girdilerini doğru şekilde işlemek için komutu olduğu gibi gönderiyoruz
    # 'exit' komutu, minishell'in testten sonra temiz bir şekilde kapanmasını sağlar.
    full_input = command + '\nexit\n'

    return subprocess.run(
        valgrind_command,
        input=full_input,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        timeout=5 # Sonsuz döngüleri yakalamak için
    )

def clean_minishell_output(output: str) -> str:
    """Minishell çıktısından prompt ve 'exit' gibi fazlalıkları temizler."""
    # Valgrind'in başlangıç ve özet çıktılarını temizle
    output = re.sub(r'==\d+==.*\n', '', output)
    
    cleaned_lines = []
    for line in output.splitlines():
        # Prompt'ları ve boş satırları atla
        if "minishell>" in line or line.strip() == "exit":
            continue
        cleaned_lines.append(line)
    return '\n'.join(cleaned_lines)

def compare_outputs(expected, actual):
    """Çıktıları karşılaştırır."""
    return expected.strip() == actual.strip()

def print_section(title, content):
    """Formatlı bir bölüm başlığı ve içeriği yazdırır."""
    print(f"\n>>> {title}")
    print(content.strip() if content.strip() else "(empty)")

def write_error_log(index, command, bash_out, mini_out, diff_out, mem_leak, stderr_diff):
    """Hataları Errors1.txt dosyasına yazar."""
    with open(ERROR_FILE, 'a') as f:
        f.write(f"🧪 Test {index}: `{command}`\n")
        f.write(">>> BASH STDOUT\n")
        f.write(bash_out.strip() + "\n\n")
        f.write(">>> MINISHELL STDOUT\n")
        f.write(mini_out.strip() + "\n\n")
        f.write(">>> STDOUT DIFF\n")
        f.write(diff_out.strip() + "\n\n")
        if stderr_diff:
            f.write(">>> STDERR DIFF\n")
            f.write(stderr_diff.strip() + "\n\n")
        if mem_leak:
            f.write(">>> MEMORY LEAK DETECTED ❌\n")
        f.write("=" * 60 + "\n\n")

def cleanup():
    """Testler tarafından oluşturulan dosyaları temizler."""
    for f in CLEANUP_FILES:
        if os.path.exists(f):
            os.remove(f)

def main():
    if not os.path.exists(MINISHELL_PATH):
        print(f"❌ minishell bulunamadı: {MINISHELL_PATH}")
        return

    # Önceki hata günlüğünü temizle
    if os.path.exists(ERROR_FILE):
        os.remove(ERROR_FILE)

    # readline.supp dosyası yoksa oluştur
    if not os.path.exists(SUPPRESSIONS_FILE):
        with open(SUPPRESSIONS_FILE, 'w') as f:
            f.write("{\n")
            f.write("   readline_leaks\n")
            f.write("   Memcheck:Leak\n")
            f.write("   fun:malloc\n")
            f.write("   fun:add_history\n")
            f.write("}\n")

    print("🔍 Testler başlıyor...\n")
    total_tests = len(TEST_CASES)
    passed_count = 0

    for i, command in enumerate(TEST_CASES, 1):
        print(f"🧪 Test {i}/{total_tests}: `{command}`")
        
        try:
            bash_result = run_shell(command)
            bash_stdout = bash_result.stdout.strip()
            bash_stderr = bash_result.stderr.strip()

            mini_result = run_minishell(command)
            mini_stdout = clean_minishell_output(mini_result.stdout)
            # Valgrind çıktısını stderr'den temizle
            mini_stderr_lines = [line for line in mini_result.stderr.splitlines() if not line.startswith('==')]
            mini_stderr = '\n'.join(mini_stderr_lines).strip()

            output_success = compare_outputs(bash_stdout, mini_stdout)
            # Stderr karşılaştırması daha esnek olmalı, çünkü hata mesajları değişebilir.
            # Genellikle var olup olmadığına bakmak yeterlidir.
            stderr_success = (not bash_stderr and not mini_stderr) or (bash_stderr and mini_stderr)
            mem_ok = mini_result.returncode != 42

            diff_out = ""
            stderr_diff_out = ""
            
            is_test_ok = output_success and stderr_success and mem_ok

            if is_test_ok:
                passed_count += 1
                print("✅ OK")
            else:
                print("❌ FAILED")
                if not output_success:
                    diff_out = '\n'.join(difflib.unified_diff(
                        bash_stdout.splitlines(), mini_stdout.splitlines(),
                        fromfile='bash_stdout', tofile='minishell_stdout', lineterm=''
                    ))
                    print_section("STDOUT DIFF", diff_out)
                
                if not stderr_success:
                    stderr_diff_out = '\n'.join(difflib.unified_diff(
                        bash_stderr.splitlines(), mini_stderr.splitlines(),
                        fromfile='bash_stderr', tofile='minishell_stderr', lineterm=''
                    ))
                    print_section("STDERR DIFF", stderr_diff_out)

                if not mem_ok:
                    print("❌ Memory leak detected")
                
                write_error_log(i, command, bash_stdout, mini_stdout, diff_out, not mem_ok, stderr_diff_out)

        except subprocess.TimeoutExpired:
            print("❌ TIMEOUT - Muhtemel sonsuz döngü!")
            write_error_log(i, command, "(timeout)", "(timeout)", "(timeout)", True, "(timeout)")
        except Exception as e:
            print(f"❌ TESTER ERROR: {e}")
            write_error_log(i, command, "(error)", str(e), "(error)", True, "(error)")

        print("\n" + "=" * 60 + "\n")
        cleanup()

    print(f"🏁 Testler tamamlandı: {passed_count}/{total_tests} başarılı.")
    if passed_count != total_tests:
        print(f"Hataların detayları için '{ERROR_FILE}' dosyasını kontrol edin.")

if __name__ == "__main__":
    main()