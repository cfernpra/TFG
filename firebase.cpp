#include "firebase.h"
#include "config.h" // Configuración global


// Variables y configuración global de Firebase
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Inicializa Firebase con las credenciales
void setupFirebase() {
  config.api_key = FIREBASE_API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Inicializar Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Conectado a Firebase Firestore");
}

// Envía una ubicación a Firestore de forma continua (a implementar si se dispone de conexión 4g)
void enviarUbicacion(String usuarioID, float lat, float lon) {
  String path = "/ubicaciones/" + usuarioID; // Ruta en Firestore

  FirebaseJson json;
  json.set("latitud", lat);
  json.set("longitud", lon);
  json.set("timestamp", String(millis() / 1000));

  if (Firebase.Firestore.createDocument(&firebaseData, FIREBASE_PROJECT_ID, "", path, json)) {
    Serial.println("Ubicación enviada a Firestore.");
  } else {
    Serial.println("Error al enviar ubicación: " + firebaseData.errorReason());
  }
}

// Lee una ubicación desde Firestore
void obtenerUbicacion(String usuarioID) {
  String path = "/ubicaciones/" + usuarioID;

  if (Firebase.Firestore.getDocument(&firebaseData, FIREBASE_PROJECT_ID, "", path)) {
    Serial.println("Datos obtenidos de Firestore:");
    Serial.println(firebaseData.payload());
  } else {
    Serial.println("Error al obtener datos: " + firebaseData.errorReason());
  }
}

// Envia ubicación solo cuando se llega a casa


void enviarDatosAlRegresar() {
  std::vector<FirebaseJson> locations = getStoredLocations();

  for (FirebaseJson location : locations) {
    if (Firebase.Firestore.createDocument(&firebaseData, FIREBASE_PROJECT_ID, "", "/ubicaciones/usuario1", location)) {
      Serial.println("Ubicación enviada.");
    } else {
      Serial.println("Error al enviar ubicación: " + firebaseData.errorReason());
    }
  }

  // Limpiar los datos almacenados localmente después de enviarlos
  clearStoredLocations();
}

void sendLocationWithReference(String userPath, float lat, float lon, String timestamp) {
  FirebaseJson json;
  json.set("userID", userPath); // userPath = "/users/user1"
  json.set("latitude", lat);
  json.set("longitude", lon);
  json.set("timestamp", timestamp);

  if (Firebase.Firestore.createDocument(&firebaseData, FIREBASE_PROJECT_ID, "", "/locations", json)) {
    Serial.println("Ubicación enviada con referencia a Firestore.");
  } else {
    Serial.println("Error al enviar ubicación: " + firebaseData.errorReason());
  }
}


void sendAlertWithReference(String userPath, String locationPath, String message, String timestamp) {
  FirebaseJson json;
  json.set("userID", userPath); // userPath = "/users/user1"
  json.set("locationID", locationPath); // locationPath = "/locations/location1"
  json.set("message", message);
  json.set("timestamp", timestamp);

  if (Firebase.Firestore.createDocument(&firebaseData, FIREBASE_PROJECT_ID, "", "/alerts", json)) {
    Serial.println("Alerta enviada con referencias a Firestore.");
  } else {
    Serial.println("Error al enviar alerta: " + firebaseData.errorReason());
  }
}


void getLocationWithReference(String locationID) {
  String path = "/locations/" + locationID;

  if (Firebase.Firestore.getDocument(&firebaseData, FIREBASE_PROJECT_ID, "", path)) {
    Serial.println("Datos de ubicación obtenidos:");
    Serial.println(firebaseData.payload());

    // Obtener el campo userID (que es un reference)
    String userPath;
    FirebaseJson json = firebaseData.jsonObject();
    json.get(userPath, "fields/userID/referenceValue");
    Serial.println("Referencia al usuario: " + userPath);

    // Leer el documento referenciado (usuario)
    if (Firebase.Firestore.getDocument(&firebaseData, FIREBASE_PROJECT_ID, "", userPath)) {
      Serial.println("Datos del usuario referenciado:");
      Serial.println(firebaseData.payload());
    }
  } else {
    Serial.println("Error al obtener datos de ubicación: " + firebaseData.errorReason());
  }
}



