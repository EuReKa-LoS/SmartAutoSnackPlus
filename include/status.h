#ifndef STATUS_H
#define STATUS_H

// Enumération pour les niveaux de croquettes
enum CroquetteLevel {
    CROQ_OK,
    CROQ_CRITIQUE
};

// Structure des états du système
struct SystemStatus {
    CroquetteLevel niveauCroquette;
    bool wifiConnected;
    bool inResetMode;
};

#endif
