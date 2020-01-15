besoin de object (dossier où on stock les id des fichiers) 
- pour le init on creer juste un fichier 
- pour le add on creer les fichiers 

besoin de index (fichier binaire mais on peut le faire en txt pour pas se faire chier)
- pour le add on modifie le fichier

besoin de head (mais pas sur)

commit id
- parent
- arbre (on creer un arbre pour chaque dossier de façon recursif) >> a.txt + [sha]
    l'arbre est modifier quand on fait un add, pas besoin quand on fait un commit simple
    blob >> commence par 16... (fichiers)
    tree >> commence par 00... (dossiers)   
- message
- auteur