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
Le cœur du programme est un automate à pile qui utilise une table de transition pour décider de l'action à effectuer à chaque étape. La pile est structurée en paires **[État, Symbole]** :

- **Décalage (Shift)** : Lorsqu'un terminal est lu, le programme pousse le symbole sur la pile, suivi de l'état cible indiqué par la table de transition. L'entrée est alors consommée.
- **Réduction (Reduce)** : Cette étape intervient lorsqu'une règle de grammaire est complète au sommet de la pile.
    - On identifie la règle à appliquer (ex: $R2: E \rightarrow E + E$).
    - On dépile $2 \times N$ éléments, où $N$ est la longueur de la partie droite de la règle. Ce doublement est nécessaire car chaque symbole sur la pile est accompagné de son état associé.
    - On utilise l'état restant au sommet de la pile pour effectuer un **Goto** : on pousse le symbole de gauche (LHS, ex: $E$) et le nouvel état correspondant à la transition État-NonTerminal.
- **Acceptation** : Si le symbole lu est `$` et que l'automate est dans l'état final, l'analyse est réussie.

### 3. Grammaire et Priorités
Le programme utilise la grammaire suivante :
1. $E' \rightarrow E$ (Axiome)
2. $E \rightarrow E + E$
3. $E \rightarrow E * E$
4. $E \rightarrow ( E )$
5. $E \rightarrow val$

Les conflits d'ambiguïté (Shift/Reduce) sont résolus manuellement dans `transitions.h` :
- **Priorité de l'Opérateur** : Dans l'état 7 (sommet $= E+E$), si le lookahead est `*`, on privilégie le décalage vers l'état 5 plutôt que la réduction immédiate, car la multiplication est prioritaire.
- **Associativité** : Si le lookahead est le même opérateur (ex: `+` après $E+E$), on réduit immédiatement pour garantir une évaluation de gauche à droite.

### 4. Calcul de la Valeur (Interprétation Sémantique)
Le calcul est réalisé via une pile de valeurs (`valStack`) gérée en parallèle de l'automate :

- **Lors du Décalage** : Si le symbole décalé est une valeur numérique (`INT`), sa valeur est poussée sur la `valStack`. Pour les opérateurs et parenthèses, une valeur neutre (0) est poussée pour maintenir la synchronisation avec la pile principale.
- **Lors de la Réduction** : 
    1. On extrait les valeurs des symboles de la partie droite de la règle. Par exemple, pour $E \rightarrow E + E$, on récupère 3 valeurs (l'opérande de droite, l'opérateur, et l'opérande de gauche).
    2. On applique l'opération mathématique :
        - $R2 (+)$ : $val1 + val3$
        - $R3 (*)$ : $val1 \times val3$
        - $R4 (par)$ : on conserve la valeur centrale $val2$.
        - $R5 (val)$ : on propage simplement la valeur du terminal.
    3. Le résultat obtenu est repoussé sur la `valStack`. Ce mécanisme permet une évaluation "montante" au fur et à mesure que l'arbre syntaxique est réduit.

## Exemple de Trace
Pour l'entree `(1+34)*123`, le programme affiche :
- Les etapes de **Decalage** (ex: lecture de `(` ou `nb`).
- Les etapes de **Reduction** (ex: transformation de `nb` en `E`).
- Le **Resultat final** calcule (ici `4305`).

## Conclusion
Ce projet illustre l'implementation d'un automate LR complet, allant de l'analyse lexicale à l'interpretation semantique, tout en gerant les ambiguïtes classiques des expressions mathematiques via une table de transitions deterministe.
