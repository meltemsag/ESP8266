String AT_Command;
String Esp_SSID = "Nucleo_ArGe"; //Enter SSID
String Esp_Password = "NucleoArGe123654"; //Enter Password
String Esp_Mode="1";
String TCP_USP_ID=""; //

//
int initial()
{
  Test_Module();
  delay(500);
  Restart_Module();
  delay(500);
  //  Firmware_Version();
  //  Deep_Sleep();
  //  Control_Echo();
  //  Set_Mode();
  //  Check_Mode();
  //  Connect_AP();
  //  Esp_Ping();
  //  List_Available_Wifi();
  //  Disconnect_AP();
  //  List_Connected_Clients();
  //  Set_DHCP();
  //  Get_MAC_Adress_Station();
  //  Set_MAC_Adress_AP();
  //  Check_IP_Station();
  //  Set_IP_Adress_AP();
  //  Get_IP_Adress_AP();
  //  Check_Connection();
  //  List_Command_Variation();
  //  Send_Data();
  //  Close_TCPUDP_Connection_Single();
}

void setup()
{
  Serial.begin(115200);
  initial();

  Restore();
  delay(500);
}

void loop()
{
  delay(2000);  
}


//cihaza bağlanılıp bağlanılmadığını kontrol eden fonksiyon
void Is_Ready()
{ 
  for(int i=0;i<5;i++)
  {
    if(!Serial.find("OK"))
      Serial.println("NOT OK");
     else{
       Serial.println("OK");
       break;
     }     
  }
}


//Yapılacak işleme göre belirlenen komutun seri kanl aracılığıyla esp8266'ya gönderilmesi için kullanılır.
void Send_Command()
{
  Serial.println(AT_Command);
}

void Response()
{
  for(int x;x<5;x++){  
    Serial.println(Serial.readString());
    delay(500);
    Serial.println(x);
    delay(500);
  }
}


//Cihaza güç verildiğinde AT komutlarının çalışıp çalışmadığını test etmek adına AT komutu yollanır.Bu fonksiyon AT komutunun gönderilmesini sağlar.
//Cevap:OK
void Test_Module()
{
  AT_Command="AT";
  Send_Command();
  Is_Ready();
}


//Sensörü yeniden başlatmak için kullanılır.
//Cevap:OK
void Restart_Module()
{
  AT_Command="AT+RST";
  Send_Command();
  Is_Ready();
} 


//Cihazın yazılım versiyonunu öğrenmek için gönderilir. Cihaz yazılımlarına göre bazı AT komutlarına başka cevaplar gözlenebilir.
//Cevap= AT version:1.2.0.0(Jul  1 2016 20:04:45)
//       SDK version:1.5.4.1(39cb9a32)
//       Ai-Thinker Technology Co. Ltd.
//       Dec  2 2016 14:21:16
//       OK
void Firmware_Version()
{
  AT_Command="AT+GMR";
  Send_Command();
  Response(); 
}


//Cihazı time değişkeninde saklanan zaman zarfında uykuya geçirmek için kullanılır . 
//Cevap==>time,OK: 1500\n OK
//Uyarı: Yükselen kenar tetiği ile cihaz uyandırılabilir.
//Cevap kontrol edilmiyor çünkü cevabın bozuk geldiği gözlenmiştir.
void Deep_Sleep()
{
  String Sleep_Time="1500";
  AT_Command="AT+GLSP="+String(Sleep_Time);
  Send_Command();
  Response();
  Is_Ready();
}


//Cihaza gönderilen mesajın tekrar geri basılması ya da basılmaması adına ayarları yapmak için kullanılır.
//0-->Geri basma kapatıldı.
//Cevap= OK
//1-->Geri basma açıldı.
//Cevap= OK
void Control_Echo()
{
  String identifier="1";
  AT_Command="ATE"+String(identifier);
  Send_Command();
  Is_Ready();
}


//Cihazda tanımlanabilecek 3 adet mod vardır.Bunları ayarlamak ve cihaza göndermek için
//kullanılır.Cihaza bir defa göndermek yeterlidir.
//Mod1=Station Mode
//Mode2=AP mode Host
//Mode3=AP+Station mode
//Cevap= OK
void Set_Mode()
{
  AT_Command="AT+CWMODE="+String(Esp_Mode);
  Send_Command();
  Is_Ready();   
}


//Cihazda tanımlanmış modu okuma işlemi için kullanılır.
//Cevap= CWMODE:(1:3)
void Check_Mode()
{
  AT_Command="AT+CWMODE?";
  Send_Command();
  Esp_Mode=Serial.parseInt();
  Serial.print("Wi-Fi mode is=");
  Serial.println(Esp_Mode);
}


//wifi bağlantısı
//Cevap= WIFI DISCONNECTED
//       WIFI CONNECTED
//       WIFI GOT IP
//       OK
void Connect_AP()
{
  AT_Command="AT+CWJAP=\""+Esp_SSID+"\",\""+Esp_Password+"\"";
  Send_Command();
  Response();
}


//bağlantı kontrolü için www.google.com adresine ping atılır.
//Cevap: 22
void Esp_Ping()
{
  String IP="172.217.169.100";
   AT_Command="AT+PING=\""+IP+"\"";
  Send_Command();
  Response();
}


//Cihazın gördüğü ağların listesini çıkarmak için kullanılan fonksiyondur.
//Cevap= CWLAP:ecn,ssid,rssi,mac
//       OK
void List_Available_Wifi()
{
  AT_Command="AT+CWLAP";
  Send_Command();
  Response();
  Is_Ready(); 
}


//Bağlantıda olunan ağdan kopmaya yarar.
//Cevap= DISCONNECT
//       OK
void Disconnect_AP()
{  
  String SAP_SSID="ESP8266";
  String SAP_Password="123456";
  String SAP_Channel="2"; //cause unknown problem
  String SAP_Enc="1"; //OPEN, 2 WPA_PSK, 3 WPA2_PSK, 4 WPA_WPA2_PSK
  AT_Command="AT+CWSAP="+SAP_SSID+","+SAP_Password+","+SAP_Channel+","+SAP_Enc;
  Send_Command();
  Is_Ready(); 
}


//Bu komut kullanıldığında erişim noktasına bağlı olan cihazların bilgileri görüntülenir.
//Cevap= 
void List_Connected_Clients()
{
  AT_Command="AT+CWLIF";
  Send_Command();
  Response(); 
  Is_Ready();
}


//Cihazın istasyon olarak mı yoksa erişim noktası olarak mı yoksa iki modu beraber mi kullanacağını belirler.
//Aynı zamanda DHCP aktif ya da deaktif hale getirebilir.
//(Dynamic Host Configuration Protocol)
//Cevap= 
void Set_DHCP()
{
  String DHCP_Mode="";
  String DHCP_En="";
  AT_Command="AT+CWDHCP_DEF="+DHCP_Mode+","+DHCP_En;
  Send_Command();
  Is_Ready();
}


//MAC adresini döndürür.
//Cevap= "dc:4f:22:51:2d:ec"
void Get_MAC_Adress_Station()
{
  AT_Command="AT+CIPSTAMAC?";
  Send_Command();
  Response();
}


//Cihazın MAC adresini ayarlamak için kullanılır.
//Cevap= WIFI DISCONNECTED
//       WIFI CONNECTED
//       WIFI GOT IP
//       OK
void Set_MAC_Adress_AP()
{
  String MAC_Adress="dc:4f:22:51:2d:ec";
  AT_Command="AT+CIPAPMAC_CUR="+MAC_Adress;
  Send_Command();
  Response();
  Is_Ready();
}

//Cihazın MAC adresini ayarlamak için kullanılır.
//Cevap= WIFI DISCONNECTED
//       WIFI CONNECTED
//       WIFI GOT IP
//       OK
void Set_MAC_Adress_AP()
{
  String MAC_Adress="dc:4f:22:51:2d:ec";
  AT_Command="AT+CIPAPMAC_DEF="+MAC_Adress;
  Send_Command();
  Response();
  Is_Ready();
}

//Cihazın IPsini döndürür.
//Cevap= 
void Check_IP_Station()
{
  AT_Command="AT+CIPSTA";
  Send_Command();
  Response();
}



//Cihazın IP adresini ayarlamak için kullanılır.
//Cevap= 
void Set_IP_Adress_AP()
{
  String IP_Adress="";
  AT_Command="AT+CIPSTA_CUR="+IP_Adress;
  Send_Command();
  Response();
}

//Cihazın IP adresini ayarlamak için kullanılır.
//Cevap= 
void Set_IP_Adress_AP()
{
  String IP_Adress="";
  AT_Command="AT+CIPSTA_DEF="+IP_Adress;
  Send_Command();
  Response();
}


//IP adresini döndürür.
//Cevap= ip:"0.0.0.0"
//       gateway:"0.0.0.0"
//       netmask:"0.0.0.0"
//       OK
void Get_IP_Adress_AP()
{
  AT_Command="AT+CIPAP?";
  Send_Command();
  Response();
  Is_Ready();
}


//Bağlantı durumunu öğrenmek için kullanılır
//Cevap= STATUS:2
void Check_Connection()
{
  AT_Command="AT+CIPSTATUS";
  Send_Command();
  Response();
}


//Tekli TCP ve UDP bağlantı kurmak için kullanılır.
//Giriş id==> Type: "TCP" ya da "UDP"(String)
//Addr: Uzaktaki IP(String)
//Port: Uzaktaki Port(String)
void Establish_TCP_UDP_Connection_Single()
{
  String Type="";
  String Addr="";
  String Port="";
  AT_Command="AT+CIPSTART="+Type+","+Addr+","+Port;
  Send_Command();
  Response();
}



//Olası komutları sıralar
//Cevap= 
void List_Command_Variation()
{
  AT_Command="AT+CIPSTART?";
  Send_Command();
  Response();
}



//TCP veya UDp bağlantısında gönderilecek olan datanın uzunluğunu ayarlamak için kullanılır.
//Cevap= 
void Set_TCPUP_Data_Single()
{
  String Single_Length="";
  AT_Command="AT+CIPSEND="+Single_Length;
  Send_Command();
  Response();
}



//TCP veya UDp bağlantısında bağlantı numarasına göre gönderilecek olan datanın uzunluğunu ayarlamak için kullanılır.
//Cevap= 
void Set_TCPUP_Data_Multiple()
{
  String Multiple_Length="";
  AT_Command="AT+CIPSEND="+TCP_USP_ID+","+Multiple_Length;
  Send_Command();
  Response();
}



//TCP veya UDP bağlantısında bağlanmışken veri gönderme görevini yapar.
//Komut işlendikten sonra ">" işareti görünür ve data göndermeye başlanır.
//Gönderilecek olan verinin uzunluğu ayarlanan veri uzunluğundan daha büyükse 
//cihaz busy cevabını verecektir.
//20msde aralıklar her paket gönderilir. Paket büyüklüğü maksimum 2048 bytedır.
//Paket içeriği +++ ile sonladnığında komut moduna geri döner. 
//Cevap= 
void Send_Data()
{
  AT_Command="AT+CIPSEND";
  Send_Command();
  Response();
}


//TCP veya UDP için bağlantıyı kapatır.
//Cevap= 
void Close_TCPUDP_Connection_Single()
{
  
  AT_Command="AT+CIPCLOSE";
  Send_Command();
  Response();
}


//TCP veya UDP için ilgili ID deki bağlantıyı kapatır.
//Cevap= 
void Close_TCPUDP_Connection_Multiple()
{
  
  AT_Command="AT+CIPCLOSE="+TCP_USP_ID;
  Send_Command();
  Response();
}


//Cihaza IP adresinin sorulduğu fonksiyondur.
//Cevap -->CIFSR:STAIP=""
void Check_IP()
{
  AT_Command="AT+CIFSR";
  Send_Command();
  Response();
}

//Cihaza IP adresinin sorulduğu fonksiyondur.
//Cevap -->CIFSR:STAIP=""
//      -->CIFSR:STAMAC=""
void Check_IP_Existince()
{
  AT_Command="AT+CIFSR?";
  Send_Command();
  Response();
}


//Çoklu bağlantının aktif olup olmadığını öğrenmek için kullanılır.
//Cevap==> 1:Tekli bağlantı
//    2:Çoklu bağlantı(maksimum 4)
void Check_Multiple_Connections()
{
  AT_Command="AT+CIPMUX?";
  Send_Command();
  Response();
}


//Çoklu bağlantının aktif olup olmadığını öğrenmek için kullanılır.
//Cevap==> 1:Tekli bağlantı
//         2:Çoklu bağlantı(maksimum 4)
//Uyarı: Bu ayar yalnızca tüm bağlantılar iptal edildikten sonra güncellenebilir.
void Set_Multiple_Connections()
{
  String CIPMUX_Mode="";
  AT_Command="AT+CIPMUX="+CIPMUX_Mode;
  Send_Command();
  Response();
}


//ESP'yi server olarak ayarlamak için kullanılır.
//Giriş==> Mode: 0 ise serverı isler(bu komuttan sonra restart atılmalıdır.
//    1 ise server yaratır.
//    Port: Bağlanılacak portun ayarlanması için kullanılır. Ayar yapılmadığı
//zaman 333'tür.
void Set_ESP_Server()
{
  String CIPSERVER_Mode="";
  String CIPSERVER_Port="";
  AT_Command="AT+CIPSERVER="+CIPSERVER_Mode+","+CIPSERVER_Port;
  Send_Command();
  Response();
}


//Bu fonksiyon yardımıyla transfer modu öğrenilebilir.
//Cevap==> 0: normal mode
//    1: transparent mode 
void Check_Transfer_Mode()
{
  AT_Command="AT+CIPMODE?";
  Send_Command();
  Response();
}


//Bu fonksiyon yardımıyla transfer modu öğrenilebilir.
//Giriş==> 0: normal mode
//         1: transparent mode
void Set_Transfer_Mode()
{
  String CIP_Mode="";
  AT_Command="AT+CIPMODE?";
  Send_Command();
  Response();
}


//Cihazın server olarak ayarlandığında zamanaşımını öğrenmek için kullanılır.
//Cevap==> time:0-7200 saniye
void Check_Server_Timeout()
{
  AT_Command="AT+CIPSTO?";
  Send_Command();
  Response();
}


//Bu fonksiyon yardımıyla transfer modu öğrenilebilir.
//Giriş==> 0: normal mode
//         1: transparent mode
void Set_Serve_Timeout()
{
  String Timeout="";
  AT_Command="AT+CIPSTO="+Timeout;
  Send_Command();
  Response();
}


//Modülün varsayılan fabrika ayarlarını geri yükler
void Restore()
{
  AT_Command="AT+RESTORE";
  Send_Command();
  Response();
}
