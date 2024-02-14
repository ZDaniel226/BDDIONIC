#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <addons/TokenHelper.h>

int led1= 23,led2= 18, led3=21;

//Conectar a una red WiFi 
const char* WIFI_SSID = "Si a de ser";//el nombre de la red
const char* WIFI_PASSWORD = "si a de ser o tal vez";//la contraseña de la red
//Recursos de Firebase
const char* API_KEY = "AIzaSyCPrDAh2PF5-kyfCihPyZGTxljDaF5dsHg";
const char* FIREBASE_PROJECT_ID = "iote3-9954c";
//CONFIGURAR UN EMAIL Y CONTRASEÑA EN AUTHENTICATION de Firebase
const char* USER_EMAIL = "benitocamela@gmail.com";
const char* USER_PASSWORD = "benito";

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setupWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;  // Ver addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);//Verificamos la version
  setupWiFi();//Llamamos la funcion de configuración wifi
  setupFirebase();//Llamamos la funcion de configuración Firebase

  pinMode(23,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(21,OUTPUT);
}

void loop(){
String path = "controlLED";//RUTA DE COLECCION
  FirebaseJson json;

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE
        Serial.print(document);
        const bool state = document["fields"]["encender"]["booleanValue"];//PARAMETRO DE CAMPOS A REVISAR
        Serial.print(" : ");
        if (strstr(document_name, "LED1") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          state ? digitalWrite(led1,HIGH) : digitalWrite(led1,LOW);
        }
        if (strstr(document_name, "LED2") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          state ? digitalWrite(led2,HIGH) : digitalWrite(led2,LOW);
        }
        if (strstr(document_name, "LED3") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          state ? digitalWrite(led3,HIGH) : digitalWrite(led3,LOW);
        }
        if (strstr(document_name, "LED4") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          state ? Serial.println("Control 4 On")  : Serial.println("Control 1 OFF");
        }
		}
	}
}
}
