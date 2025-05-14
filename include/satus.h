#ifndef STATUS_H
#define STATUS_H

// État du niveau de croquettes
enum CroquetteLevel {
    CROQ_OK,
    CROQ_CRITIQUE
};

// Structure centrale des états système
struct SystemStatus {
    CroquetteLevel niveauCroquette;
    bool wifiConnected;
    bool inResetMode;
};

#endif
