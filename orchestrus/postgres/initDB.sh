#!/bin/bash
set -e

psql -v ON_ERROR_STOP=1 --username "postgres" --dbname 'IGL601' <<-EOSQL
    CREATE TABLE worker (
        ip VARCHAR (15) PRIMARY KEY,
        port VARCHAR (4),
        status BOOLEAN 
    );

    CREATE TABLE image (
        name VARCHAR (50) PRIMARY KEY,
        docker_id VARCHAR (50),
        worker_ip VARCHAR (15),
        worker_port INTEGER,
        image_ports VARCHAR (15)
        CONSTRAINT worker_ip_fkey FOREIGN KEY (worker_ip)
            REFERENCES worker (ip)
    );

EOSQL