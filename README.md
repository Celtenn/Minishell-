// readline dan gelen leaki engellemek "valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --track-fds=yes ./minishell"
# Minishell

✅ 1. Proje Gereksinimlerini Oku ve Anla
Proje dokümanını dikkatlice oku. Minishell projesinde genelde istenenler:

Komutları işleyebilme (ls, echo, vs.)

Pipe (|)

Redirection (<, >, >>, <<)

Built-in komutlar (cd, export, unset, env, exit, pwd, echo)

Ortam değişkenleri yönetimi

CTRL+C, CTRL+D, CTRL+\ gibi sinyallerle doğru tepki

Global exit status yönetimi

✅ 2. Temel Yapıyı Oluştur

📁 Dosya Yapısı Örneği:
css
Kopyala
Düzenle
minishell/
│
├── src/
│   ├── main.c
│   ├── parser/
│   ├── executor/
│   ├── builtin/
│   ├── signals/
│   └── utils/
├── include/
│   └── minishell.h
├── Makefile
└── README.md

✅ 3. Basit Prompt ile Başla

✨ readline ile bir input al:
c

#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;
        add_history(input);
        free(input);
    }
    return (0);
}
Bu sayede kullanıcıdan sürekli komut alabilirsin.

✅ 4. Parsing (Tokenize Etme)
🔍 Yapılacaklar:
Komutu ve argümanları parçalara ayır.

Quote’lara saygı göster: "echo hello world" ile 'echo hello world'

Redirectionları (>, >>, <, <<) ve pipe’ları (|) tanı.

Bash'teki gibi export VAR=value gibi komutları anlamlandır.

Her komut bir yapı (struct) içinde tutulmalı.

✅ 5. Built-in Komutları Yaz
Komut	Açıklama
echo	Argümanları yazar. -n desteği gerekir.
cd	Dizin değiştirir.
pwd	Çalışılan dizini yazdırır.
export	Ortam değişkeni ekler/günceller
unset	Ortam değişkenini siler
env	Ortam değişkenlerini listeler
exit	Shell'den çıkar

Built-in komutlar dışındaki komutlar için execve çağrısı yapılmalı.

✅ 6. Redirection (Yönlendirme) Desteği
🚀 Desteklenmesi gerekenler:
>: stdout dosyaya yönlendirme

>>: stdout dosyaya ekleme

<: stdin dosyadan alma

<<: here_doc (kullanıcının girişini belirli bir anahtara kadar oku)

dup2() sistem çağrısı ile yönlendirme yapılır.

✅ 7. Pipe (|) Desteği
Bir komutun çıktısını diğer komutun girdisi yap.

fork() ile her komutu bir child process olarak çalıştır.

pipe() ile iki process arasında bağlantı kur.

Çoklu pipe’ları destekle (örneğin: ls | grep txt | wc -l)

✅ 8. Sinyal Yönetimi
🎯 Gerekli sinyaller:
CTRL+C (SIGINT) → prompt sıfırlanmalı

CTRL+\ (SIGQUIT) → bazı durumlarda çıkış yapılmalı

CTRL+D → input NULL olur, shell kapanmalı

signal() veya sigaction() kullanarak bu sinyallere özel davranış tanımlanmalı.

✅ 9. Çevresel Değişkenleri Yönet
Başlangıçta envp’yi kopyala.

export, unset, env gibi komutlarla güncelle.

execve çağrısı yapılırken ortam değişkenleri hazırlanmalı.

✅ 10. Global Exit Status Yönetimi
Her komutun sonunda global bir exit_status güncellenmeli.

$? çağrıldığında son exit code döndürülmeli.

✅ 11. Bellek Yönetimi ve Leak Kontrolü
Tüm malloclar free ile serbest bırakılmalı.

Her bir input’tan sonra kullanılan hafıza temizlenmeli.

valgrind ile test yap.

✅ 12. Bonus (Zorunlu Değil Ama Tavsiye Edilenler)
Wildcard desteği (*)

Logical operators (&&, ||)

Parantez desteği

Komut geçmişi dosyaya kaydetme

✅ 13. Test Etme ve Son Rötuşlar
Gerçek shell’de yaptığın testleri burada da dene.

Komutlar sırayla düzgün çalışıyor mu?

Edge case'leri test et: boş input, tek quote, çoklu pipe, vs.

✳️ Ekstra İpuçları:
Kodunu modüler yaz. Her .c dosyası tek bir işi yapsın.

Header dosyasını temiz tut.

Sık sık make clean && make && valgrind ./minishell yaparak kontrol et.

Bash’te deneyip çalışmasını anlayamadığın komutları strace veya bash -x ile takip et.
--------------------------------------------------------------------------------------------------------------------------------------------------------
✅ GENEL TEST KONTROL LİSTESİ (MANDATORY ÖZELLİKLER)
1. 🔹 Giriş & Prompt
 readline() prompt'u gösteriyor mu?

 Ctrl-D (EOF) shell'den çıkıyor mu?

 Ctrl-C yeni satıra geçip prompt'u gösteriyor mu?

2. 🔹 Tokenizer (lexer)
 "çift tırnak" ve 'tek tırnak' içindeki boşluklar korunuyor mu?

 |, <, >, <<, >> gibi özel karakterler doğru tanınıyor mu?

 echo hello | wc gibi pipe'lı komutlar tokenize ediliyor mu?

 Tırnaklar kapatılmadığında hata döndürülüyor mu?

3. 🔹 Parser
 echo hello | wc komutu iki ayrı t_cmd objesi olarak parse ediliyor mu?

 Redirection'lar (>, <, >>, <<) doğru parse ediliyor mu?

 cmd->argv dizisi null sonlandırılmış mı?

✅ KOMUT ÇALIŞTIRMA VE PIPE
4. 🔹 Komut Yürütme (execve, pipe)
 ls çalışıyor mu?

 ls -l | grep .c gibi komutlar pipe'la doğru akıyor mu?

 cat < input.txt input dosyasını okuyor mu?

 echo hello > output.txt çıktıyı dosyaya yazıyor mu?

 >> çıktıyı ekliyor mu?

 << DELIM heredoc girdisi çalışıyor mu?
 
✅ ENVIRONMENT VARIABLE EXPANSION

5.
 echo $HOME ortam değişkenini gösteriyor mu?

 echo $? son komutun exit status'unu gösteriyor mu?

 export VAR=value sonrası echo $VAR doğru değer döndürüyor mu?

 unset VAR sonrası echo $VAR boş döndürüyor mu?

✅ BUILT-IN KOMUTLAR
Komut	Kontrol
cd	cd .., cd /, cd dosya çalışıyor mu?
pwd	pwd mevcut dizini gösteriyor mu?
echo	echo hello, echo -n no-newline
exit	exit, exit 42 shell'den çıkıyor mu?
env	Ortam değişkenlerini listeliyor mu?
export	Yeni değişken ekliyor ve $VAR ile görünüyor mu?
unset	Değişkeni ortamdan kaldırıyor mu?

✅ BELLEK & HATA YÖNETİMİ
 Tüm malloc, strdup, realloc işlemleri NULL kontrolü içeriyor mu?

 Bellek sızıntısı (valgrind ile test edilebilir) var mı?

 Hatalı quote/pipe/redirect gibi hatalar düzgün mesaj veriyor mu?

 Shell crash etmiyor mu? (örneğin boş echo, export, unset çağrısı)
