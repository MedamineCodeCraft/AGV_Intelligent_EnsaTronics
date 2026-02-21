# 📘 AGV – Asservissement Moteur Droit (M2)

## 🎯 Objectif

Ce module implémente l’asservissement en vitesse du **moteur droit (M2)** d’un AGV différentiel en s’appuyant sur :

- **Arduino Uno**
- **Adafruit Motor Shield V1 (L293D)**
- **Encodeur incrémental sur la pin 3**
- **Contrôleur PID**

Ce fichier représente le **niveau 1 de contrôle** (boucle interne de vitesse) dans l’architecture du robot.

## ⚙️ Architecture du système

Boucle interne de vitesse :

**Consigne → PID → PWM → Moteur → Encodeur → Mesure de vitesse**

Le moteur est piloté via la librairie `AFMotor`, et la vitesse réelle est estimée à l’aide d’une interruption externe sur la pin 3.

## 🔌 Configuration matérielle

### Moteur

- Connecté sur la sortie **M2** du Motor Shield

### Encodeur

- Signal encodeur → **Pin 3** Arduino
- **GND commun** avec l’Arduino
- Utilisation de l’interruption externe

### Alimentation

- Batterie externe pour moteurs (**6–12V recommandé**)
- Masse commune avec la carte Arduino

## 🧠 Fonctionnement du programme

Le programme propose deux modes de commande via le **Serial Monitor (9600 baud, No line ending)**.

### 1) 🟢 Mode simple (PWM direct)

Entrer une valeur PWM entre 0 et 255.

Exemple :

```text
150
```

→ Le moteur tourne directement avec **PWM = 150**.

### 2) 🔵 Mode PID (asservissement)

Pour activer le PID, entrer une valeur comprise entre **1000 et 1255**.

Exemple :

```text
1150
```

→ Le PID est activé avec une consigne de vitesse de **150**.

La conversion est :

```text
consigne = valeur_reçue - 1000
```

Le système ajuste automatiquement le PWM pour maintenir la vitesse demandée.

### 3) 🔴 Arrêt

```text
0
```

→ Arrêt du moteur.

## 🛠 Réglage du PID

Paramètres à ajuster :

- `Kp`
- `Ki`
- `Kd`

Méthode conseillée :

1. Mettre `Ki = 0` et `Kd = 0`
2. Augmenter `Kp` jusqu’à obtenir une réponse rapide
3. Ajouter un petit `Ki` pour corriger l’erreur statique
4. Ajouter un petit `Kd` (ex. `0.05`) en cas d’oscillations/vibrations

Repères pratiques :

- **Trop lent** → augmenter `Kp`
- **Oscillation** → diminuer `Kp`
- **Petite erreur permanente** → augmenter légèrement `Ki`
- **Vibrations** → ajouter un petit `Kd`

## 📊 Test et validation

Tests recommandés :

- Test roue levée
- Test avec charge
- Test de compensation de perturbations
- Observation de la stabilité de vitesse

Critères attendus :

- Le moteur suit la consigne
- Le moteur revient à la vitesse demandée après perturbation
- Le comportement reste stable (oscillations limitées)

## 🚀 Prochaines étapes

1. Reproduire la même structure pour le moteur gauche
2. Mettre en place **2 PID indépendants**
3. Synchroniser les deux roues
4. Intégrer la boucle externe (suivi de ligne/navigation)

## 📁 Structure du dossier

```text
/Motor_Control/
  ├── RIGHT PID MOTOR.INO
  └── README.md
```

## 🏁 État actuel

- ✅ Moteur droit commandable
- ✅ Encodeur opérationnel
- ✅ PID implémenté
- ⏳ Moteur gauche à développer
- ⏳ Synchronisation des roues à intégrer
