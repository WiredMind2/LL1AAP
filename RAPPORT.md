# Rapport du Programme d'Analyseur Syntaxique LR

## Description Generale
Ce programme est un analyseur syntaxique (parser) de type **Decalage-Reduction (LR)** capable d'evaluer des expressions arithmetiques. Il transforme une chaîne de caracteres (ex: `(1+2)*3`) en un resultat numerique tout en verifiant la validite syntaxique de l'expression selon une grammaire definie.

## Fonctionnement Technique

### 1. Analyse Lexicale (Lexer)
Le `Lexer` decoupe la chaîne d'entree en unites elementaires appelees **Symboles** :
- `INT` : pour les nombres entiers (ex: `123`).
- `PLUS`, `MULT` : pour les operateurs `+` et `*`.
- `OPENPAR`, `CLOSEPAR` : pour les parentheses `(` et `)`.
- `FIN` (`$`) : marqueur de fin de chaîne.

### 2. Analyse Syntaxique (Automate LR)
Le cœur du programme est un automate à pile qui utilise une table de transition pour decider de l'action à effectuer à chaque etape :

- **Decalage (Shift)** : On pousse le symbole lu et le nouvel etat cible sur la pile.
- **Reduction (Reduce)** : Lorsqu'une regle de grammaire est reconnue au sommet de la pile, on remplace ses elements par le symbole de gauche de la regle (LHS).
- **Goto** : Determine le prochain etat apres une reduction.
- **Acceptation** : Si on atteint l'etat final avec le symbole `$`, l'expression est valide.

### 3. Grammaire et Priorites
Le programme utilise la grammaire suivante :
1. $E' \rightarrow E$ (Axiome)
2. $E \rightarrow E + E$
3. $E \rightarrow E * E$
4. $E \rightarrow ( E )$
5. $E \rightarrow val$

Les conflits de priorite (ex: entre `+` et `*`) et d'associativite sont resolus directement dans la table d'analyse (`transitions.h`) :
- La multiplication `*` est prioritaire sur l'addition `+`.
- Les deux operateurs sont associatifs à gauche.

### 4. Calcul de la Valeur
Une pile de valeurs (`valStack`) est maintenue en parallele de la pile d'etats. Lors de chaque reduction, l'operation mathematique correspondante est effectuee sur les valeurs extraites de la pile, et le resultat est repousse sur celle-ci.

## Exemple de Trace
Pour l'entree `(1+34)*123`, le programme affiche :
- Les etapes de **Decalage** (ex: lecture de `(` ou `nb`).
- Les etapes de **Reduction** (ex: transformation de `nb` en `E`).
- Le **Resultat final** calcule (ici `4305`).

## Conclusion
Ce projet illustre l'implementation d'un automate LR complet, allant de l'analyse lexicale à l'interpretation semantique, tout en gerant les ambiguïtes classiques des expressions mathematiques via une table de transitions deterministe.
