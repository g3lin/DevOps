all: worker

buildWorker: 
	docker build worker -t worker

worker: buildWorker
	docker run -it worker

