# TP3 IGL601
Travail par Julien Brosseau et Antoine Gélin
Travail réalisé : toutes les fonctionalités obligatoires, aucun bonus

## Instructions
- Lancer le docker-compose depuis le dossier orchestrus avec "docker-compose pull" puis "docker-compose up". 
- Vous devrez sûrement définir un mot de passe de Postgres (export POSTGRES_PASSWORD=MDPàModif)
- Se connecter au client sur la même machine avec "docker attach orchestrus-core" 
- Éventuellement taper sur ENTRÉE pour avoir les instructions, la ligne s'affichant souvent avant qu'on s'attache au conteneur
- Suivre les instructions du client, tapez "help" pour plus de détais
- Lancer le worker sur n'importe quelle machine même distante avec make runWorker. Il se lance par défaut sur le port 4242

Les images sont toutes compilées sous architecture AMD64 et disponibles sur DockerHub.

