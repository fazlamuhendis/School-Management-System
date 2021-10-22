# School-Management-System
# School-Management-System
Displaying the data taken from the data file with json extension in a user interface, adding and deleting new elements to the tables via the interface, updating the tables in json format after making changes.

/************************* Arayüz Kullanım *************************/ 

Arayüz ilk açıldığında show table butonu dışındaki butonlar aktif değildir, show table butonuna basıldığıdında json dosyasındaki veri seti öğrenciler , öğretmenler ve sınıf tablarında tablolarda gösterilmektedir.Tabloda gösterildikten sonra her tabın altında ekleme ve silme butonları ve güncelleme butonu(update) aktif olacaktır.Update işlemi başarılı bir şekilde yapıldıktan sonra statusbar da durum bilgisi görünmektedir.

Ekleme işlemi ---> + butonuna basıldığında kaç adet eleman varsa onun hep bir altına yeni bir satır oluşturur.

Silme işlemi  ---> satıra bir kere basıldığında tablo komple seçilir , bu ilgili tabın(öğrenci , öğretmen ,sınıf) bir üyesini temsil etmektedir ,  basılı hale gelen satır farklı bir renkte gorülür (seçili anlamına gelir.)Satır seçiliyken - butonuna basıldığında o satır yani o üye o sınıftan silinmiş olur.

Güncelleme    ---> Tablolardaki herhangi bir üyenin herhangi bir özelliğine (indexe) çift click yapıldığında , yazım aktif olmuş olur ve ilgili güncelleme yapılabilir.


Yapılmış olan güncelleme silme ekleme işlemlerinden sonra update butonuna tıklandığında tablodaki değişiklikler olduğu gibi json veri setine kaydedilir.

NOT: json dosyası derlenmiş olan build-school_management_system..  dosyasında bulunmalıdır.Git dosyasında bunu veriyorum ancak proje derlenince ekstra bir dosya çıkartabiliyor bazen.Normalde .json formatlı dosyayı kullanıcının kendini seçmesi şeklinde ayarlayacaktım ancak yolu verirkek linux ve windows bilgisayarlarda uyumluluk sorunu olduğu için direk içinde dahil olan dosya ismini vererek olduğu yerden dosyayı import etsin şeklinde ayarlamak durumunda kaldım.

NOT(2) :Json sınıfına dosyayı tekrardan update ederken sıralı olarak kaydetmiyor.Örn :  Studentlar 1,2,3,4,5,6,7,8,9,10  yerine 1,2,10,3,4,5,6,7,8,9 olarak sıralı bir şekilde kaydoluyor.Ancak 10 numaranın içindeki veriler yine 10 numaralı öğrencinin ismi soyismi yaşı vb. değerlerde veya import ederken tabloda gösterirken hiçbir sorun yok , sadece sıralı kaydetmeme rağmen json un içinde 10 numaralı öğrencinin özellikleri (tamamı doğru olan tablodaki gibi olan özellikler) 2. öğrenciden sonra görünüyor. 

/************************* Tasarım *************************/ 

Tasarım tamamen olabilecek en kolay kullanım olsun şeklinde yapılmaya çalışıldı.Yukarda belirtmiş olduğum arayüz kullanım kısmını okumadan bile 2 kurcalanarak yapılabilecek şeklinde bir yaklaşım kullanıldı.Öncelikle tablo güncelleme ekleme silme gibi butonlara basınca yeni bir form açılıp oradaki linelara o değerleri girip ok butonuna basıldıktan sonra tabloda tekrar gösterilecek şeklinde yapılmıştı , ancak bu tamamen bir kat fazla yorucu kullanım zorluğu ve performansı negatif etkilediğinden dolayı direk gösterilen tablo üzerinden basitçe yapılmaya çalışıldı.Tasarımdaki rekler olabildiğince sadece ve öğrenci kayıt sistemi olduğu için renkli cıvıl cıvıl yerine koyu tonlar tercih edildi.
