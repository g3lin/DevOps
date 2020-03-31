all: worker

buildWorker: 
	docker build worker -t worker

worker: buildWorker
	docker run -v /var/run/docker.sock:/var/run/docker.sock -it worker

