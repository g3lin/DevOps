all: runworker

login:
	echo $(DOCKER_HUB_GELINA) |	docker login -u gelina --password-stdin
buildWorker: 
	docker build worker -t gelina/worker

pushWorker:login buildWorker
	docker push gelina/worker

buildBDD: 
	docker build bdd-controller -t gelina/bdd-controller

pushBDD:login buildBDD
	docker push gelina/bdd-controller

buildPostgres: 
	docker build postgres -t gelina/postgres

pushPostgres:buildPostgres
	docker push gelina/postgres

runworker: buildWorker
	docker run -v /var/run/docker.sock:/var/run/docker.sock -p 4242:4242 -it worker






