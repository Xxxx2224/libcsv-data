# LibCsv-Data

Bu kutuphane, CSV formatindaki veri setlerini FANN (Fast Artificial Neural Network) kutuphanesinin kullanabilecegi
DATA formata donusturur.harici bir bagimlilik olmadan gomulu sistemler icin tasarlanmistir.

## Tasarim Tercihleri

1. **Bellek Yonetimi ve Hiz:**
   Tasarim tercihimiz veri setini tek seferde bellege alip, ayraçlari null terminator(`\0`) ile degistirip, her null terminator'un solunda, bir onceki terminatorden hemen sonra olacak sekilde pointer tutmaktir. Her sutun icin bir pointer, her sutun pointer dizisi icin ise bir satir pointer'i tutulmaktadir.

   Amac az I/O islemi yaparak veri uzerinde hizli gezinmektir. Tek seferde I/O islemi yapilmiyor ama buffer ile her 64KB'da bir okuma yapiliyor. Evet performans odakli yaklastim ama tek seferde I/O islemi, dosyadan dosyaya degismekle birlikte cok fazla bellek harcayabilir. Biraz dengeli hareket ettim bu konuda, zaten tek seferde I/O islemini kernel parcalayarak diske gonderecekti.

2. **Alternatif Senaryo (Not):**
   2 farkli senaryo var: ilki saf hiz, digeri saf dusuk bellek.

   Aslinda zaten hiz odakli dusunerek hareket ettim ama birkac konuda dengeli davrandim. Belki tek sefer I/O islemi yaparak az kernel cagrisi gibi optimizasyonlar yapilabilirdi ama emin degilim, aklima suanlik bunlar geldigi icin kazanci cok mantikli gelmedi ve vazgectim.

   Dusuk bellekler icin yeni tasarim dusunulebilir ancak hizdan kayip verilecektir. Satir satir okuyup her ayrac bulundugunda kelime basini tutan pointeri ayraci tespit ettigimiz noktaya kadar bellegi dosyaya yazmak ve satir bittikce alani birakip yeni satir okumak seklinde bir yontem izlenebilir. Bu yontemin eksisi cok fazla sistem cagrisi ve I/O islemi icermesidir, yani dusuk performans demektir.

## Derleme ve Kullanim

Kutuphaneyi derlemek ve test etmek icin makefiles kullanilabilir:

```bash
make
./fann_csv_test
```

