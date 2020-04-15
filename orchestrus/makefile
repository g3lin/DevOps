all: buildWorker buildCore buildBDD buildPostgres

login:
	echo $(DOCKER_HUB_GELINA) |	docker login -u gelina --password-stdin
buildWorker: 
	docker build worker -t gelina/worker

pushWorker: buildWorker
	docker push gelina/worker

buildBDD: 
	docker build bdd-controller -t gelina/bdd-controller

pushBDD: buildBDD
	docker push gelina/bdd-controller

buildCore: 
	docker build orchestrus-core -t gelina/orchestrus-core

pushCore:buildCore
	docker push gelina/orchestrus-core

buildPostgres: 
	docker build postgres -t gelina/postgres

pushPostgres:buildPostgres
	docker push gelina/postgres

# -----------------------------------------------------------------------------------
network:
	docker network create orchestrus

runworker: buildWorker 
	docker run --name worker --network orchestrus_orchestrus -v /var/run/docker.sock:/var/run/docker.sock -p 4242:4242 -it gelina/worker

runCore: buildCore 
	docker run --network orchestrus_orchestrus -it gelina/orchestrus-core






