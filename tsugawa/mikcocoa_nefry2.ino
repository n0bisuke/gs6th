#include <Nefry.h>
#include <Nefry_Milkcocoa.h>

#include "DHT.h"
#define DHTPIN D4     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

Nefry_Milkcocoa *milkcocoa;

DHT dht(DHTPIN, DHTTYPE);

char *datastore;
void onpush(DataElement *elem) {//MilkcocoaのOn関数と同一
  //データストアにデータが届いたときに呼び出される
  Nefry.print("onpush:");
  Nefry.println(elem->getInt("sw"));//swというデータがあるとき表示されます
}

void setup() {
  dht.begin();
  milkcocoa->print();//Setup ModuleページにAPPIDの表示をする
  milkcocoa = Nefry_Milkcocoa::begin();//milkcocoaと接続に必要になる処理をします。
  datastore = Nefry.getConfStr(3);//Setup Moduleページに入力されたデータストア名を保存します。
  Nefry.println( milkcocoa->on( datastore, "push", onpush) ? "Milkcocoa onPush OK" : "Milkcocoa onPush NG" );//on関数を有効にします。
  }

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  Nefry.println(t);
  DataElement elem = DataElement();
  elem.setValue("Humidity", h );
  elem.setValue("Temperature", t );
  milkcocoa->push(datastore, &elem);//Milkcocoaに送信
  Nefry.ndelay(10*1000);
}
