# Robot auto-équilibré à deux roues

Projet de fin d'études - Licence 3 en Automatique  
Réalisé par une équipe de 4 étudiants.

Ce projet consiste à concevoir un robot capable de se stabiliser sur deux roues en temps réel. L'équilibrage est réalisé à l'aide d'un capteur inertiel (MPU6050) et d’un algorithme PID implémenté sur une carte Arduino Nano. Le robot peut également être contrôlé via une application Android utilisant une connexion Bluetooth.

## Objectifs du projet

- Réaliser un robot physique auto-équilibré
- Lire l’inclinaison via un gyroscope et un accéléromètre (MPU6050)
- Estimer l’angle à l’aide d’un filtre complémentaire
- Implémenter une régulation PID temps réel
- Piloter les moteurs à l’aide d’un pont en H (L298N)
- Ajouter la possibilité de contrôle à distance via Bluetooth

## Composants utilisés

- Arduino Nano
- MPU6050 (accéléromètre + gyroscope)
- Module L298N
- Deux moteurs DC avec roues
- Module Bluetooth HC-05
- Batterie Li-Po
- Châssis fabriqué à la main

## Détails techniques

- Langage de programmation : Arduino (C/C++)
- Lecture des données en I2C
- Fusion des données avec un filtre complémentaire
- PID : Kp = 40, Ki = 0.05, Kd = 0.8
- Arrêt automatique en cas de dépassement d’angle critique
- Contrôle par smartphone via module Bluetooth

## Aperçu

![Photo du robot](media/photo.jpg)

## Vidéo de démonstration

[Voir la vidéo](https://www.youtube.com/watch?v=LIEN_VIDÉO_ICI)

## Structure du projet

- `robot_balance.ino` : code source Arduino
- `README.md` : description du projet
- `media/photo.jpg` : image du robot
- `media/robot_demo.jpg` : miniature vidéo

## Contact

Pour toute question ou suggestion, n'hésitez pas à nous contacter via GitHub ou LinkedIn.
