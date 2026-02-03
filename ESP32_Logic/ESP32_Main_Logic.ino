// Définition des catégories basées sur tes 4 tags
const int NB_TAGS = 4;
String tagsAutorises[NB_TAGS] = {"43 37 10 2D", "B3 0E FE 1B", "62 51 20 4E", "54 1F 2F 00"};
String categories[NB_TAGS] = {"A", "B", "C", "D"}; // Catégories A, B, C et D [cite: 6, 51]

void setup() {
  Serial.begin(9600); // Communication avec l'Arduino [cite: 21, 41]
  Serial.println("ESP32 Prêt pour l'identification...");
}

void loop() {
  if (Serial.available() > 0) {
    String uidRecu = Serial.readStringUntil('\n');
    uidRecu.trim();
    
    if (uidRecu.length() > 0) {
      identifierEtRouter(uidRecu);
    }
  }
}

void identifierEtRouter(String uid) {
  bool trouve = false;
  for (int i = 0; i < NB_TAGS; i++) {
    if (uid == tagsAutorises[i]) {
      Serial.print("Produit détecté: Catégorie "); [cite: 13, 51]
      Serial.println(categories[i]);
      
      // Logique de routage vers l'emplacement [cite: 5, 52]
      envoyerCommandeAGV(categories[i]);
      trouve = true;
      break;
    }
  }
  if (!trouve) Serial.println("Erreur: Tag non reconnu");
}

void envoyerCommandeAGV(String cat) {
  // Ici, tu ajouteras le code pour piloter les moteurs vers la zone A, B, C ou D
  Serial.print("Routage en cours vers zone: ");
  Serial.println(cat);
}