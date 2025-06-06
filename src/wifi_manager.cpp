#include "wifi_manager.h"
#include "settings_storage.h"
#include <LittleFS.h>
#include <Arduino.h>
#include <ArduinoJson.h>

// Constantes tirées des variables d'environnement
// Utilisation des variables d'environnement (PlatformIO build_flags)
// Legacy keep for debuging pursposes only, as we are using a custom WiFiManager class now
/*const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;
void initWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Tentative de connexion à : ");
  Serial.print(ssid);
}*/
WiFiManagerCustom wifi_manager;

const WiFiCredentials& WiFiManagerCustom::getCredentials() const {
  return currentCredentials;
}

void WiFiManagerCustom::connectToWiFi(const WiFiCredentials &creds) {
  Serial.printf("🔌 Tentative de connexion à : %s\n", creds.ssid.c_str());

  WiFi.mode(WIFI_STA);
  WiFi.begin(creds.ssid.c_str(), creds.password.c_str());

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Connexion Wi-Fi réussie !");
    Serial.print("Adresse IP : ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Échec de connexion Wi-Fi");
  }
}

void WiFiManagerCustom::startAccessPoint() {
    const char* ap_ssid = "AutoSnack";
    const char* ap_password = "0123456789";

    WiFi.mode(WIFI_AP);
    bool result = WiFi.softAP(ap_ssid, ap_password);

    if (!result) {
        Serial.println("Échec du démarrage du point d'accès !");
        return;
    }

    Serial.println("Point d'accès démarré !");
    Serial.print("SSID : ");
    Serial.println(ap_ssid);
    Serial.print("Mot de passe : ");
    Serial.println(ap_password);
    Serial.print("Adresse IP : ");
    Serial.println(WiFi.softAPIP());

    // Initialise le système de fichiers LittleFS
    if (!LittleFS.begin()) {
        Serial.println("Erreur de montage LittleFS");
    } else {
        Serial.println("LittleFS monté avec succès");
    }

    // Route racine "/" - envoi du fichier index.html
    server.on("/", HTTP_GET, [this]() {
        File file = LittleFS.open("/index.html", "r");
        if (!file || file.isDirectory()) {
            server.send(404, "text/plain", "Fichier index.html introuvable");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    // Route POST /save pour recevoir les infos Wi-Fi en JSON
    server.on("/save", HTTP_POST, [this]() {
    if (server.hasArg("plain")) {
      const String body = server.arg("plain");
      Serial.println("Corps reçu : " + body);

      StaticJsonDocument<256> doc;
      DeserializationError error = deserializeJson(doc, body);

      if (error) {
        server.send(400, "application/json", "{\"message\":\"Erreur JSON\"}");
        return;
      }

      File file = LittleFS.open("/wifi.json", "w");
      if (!file) {
        server.send(500, "application/json", "{\"message\":\"Erreur ouverture fichier\"}");
        return;
      }

      serializeJson(doc, file);
      currentCredentials = WiFiCredentials{ doc["ssid"].as<String>(), doc["password"].as<String>() };
      file.close();
      Serial.println("✅ Données Wi-Fi enregistrées dans /wifi.json");
      // Basculer hors du mode config
      inConfigMode = false;

      server.send(200, "application/json", "{\"message\":\"Données enregistrées !\"}");
    } else {
      server.send(400, "application/json", "{\"message\":\"Aucun corps reçu\"}");
    }
  });

    server.begin();
    Serial.println("Serveur web démarré sur 192.168.4.1");
}


void WiFiManagerCustom::handleClient() {
  if (debugMode) {
    server.handleClient();  // Toujours traiter les requêtes HTTP en mode AP
    // Serial.println("Requête reçue"); // Optionnel, ou à limiter fortement
  }
}

void WiFiManagerCustom::setDebugMode(bool debug) {
  debugMode = debug;
}

void WiFiManagerCustom::begin() {
  if (!LittleFS.begin()) {
    Serial.println("❌ Échec du montage LittleFS");
    inConfigMode = true;
    startAccessPoint();
    return;
  }
  Serial.println("✅ LittleFS monté avec succès");

  currentCredentials = loadWiFiCredentials();

  if (!currentCredentials.isValid()) {
  Serial.println("ℹ️ Données Wi-Fi invalides ou absentes, passage en mode configuration");
  inConfigMode = true;
  startAccessPoint();
  return;
}

Serial.println("📶 Données Wi-Fi lues :");
Serial.println("  SSID : " + currentCredentials.ssid);
Serial.println("  Mot de passe : " + currentCredentials.password);

inConfigMode = false;
connectToWiFi(currentCredentials);
}


void updateWiFiStatus(SystemStatus &status) {
  static unsigned long lastPrint = 0;
  static unsigned long lastReconnectAttempt = 0;
  unsigned long now = millis();

  wl_status_t wifiState = WiFi.status();

  if (wifiState == WL_CONNECTED) {
    if (!status.wifiConnected) {
      Serial.println("\n✅ Wi-Fi connecté !");
      Serial.print("IP locale : ");
      Serial.println(WiFi.localIP());
    }
    status.wifiConnected = true;
  } else {
    status.wifiConnected = false;

    if (now - lastPrint > 1000) {
      Serial.print(".");
      lastPrint = now;
    }

    if (now - lastReconnectAttempt > 10000) {
      Serial.println("\n🔄 Tentative de reconnexion Wi-Fi...");

      const WiFiCredentials &creds = wifi_manager.getCredentials();

      if (creds.isValid()) {
        WiFi.disconnect();
        WiFi.begin(creds.ssid.c_str(), creds.password.c_str());
      } else {
        Serial.println("❌ Pas d'identifiants Wi-Fi valides pour se reconnecter.");
      }

      lastReconnectAttempt = now;
    }
  }
}