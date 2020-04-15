using System;

using Docker.DotNet;
using Docker.DotNet.Models;

using System.Collections.Generic;

using System.Net;  
using System.Net.Sockets;  
using System.Text;  
using System.Threading.Tasks;
using System.Threading;

using System.Text.Json;

using System.IO;


/**

On va utiliser le SDK de docker en C# par MS
https://github.com/microsoft/Docker.DotNet

**/

namespace worker
{
    public class Program
    {
        DockerClient client;

        static void Main(string[] args)
        {
            Program prog = new Program();
            prog.Main();

            SocketsManager socket = new SocketsManager(prog);
            socket.StartListening();

        }


        private void Main(){
            // Création du client Docker
            client = new DockerClientConfiguration(
                new Uri("unix:///var/run/docker.sock"))
            .CreateClient();

            // // Pull de l'image
            // ImagesCreateParameters image = new ImagesCreateParameters
            // {
            //     FromImage = "hello-seattle",
            //     Tag = "linux",
            // };
            // await createContainer(client, image);
            // bool status = await startContainer(client, "hello-world", new string[0]);
            // Console.WriteLine(status.ToString());
        }

        public string parseCommand(string content){
            string rep = "";
            try
            {
                JsonDocument document = JsonDocument.Parse(content);
                JsonElement root = document.RootElement;
                JsonElement request = root.GetProperty("request");

                if(request.ToString().Equals("imageLaunch"))
                    rep = imageLaunch(root).GetAwaiter().GetResult();
                
                else if(request.ToString().Equals("imageDL"))
                    rep = imageDL(root).GetAwaiter().GetResult();
                

            }
            catch (System.Exception)
            {
                
                throw;
            }


            return rep;
        }

        private async Task<string> imageLaunch(JsonElement root){
            String rep = "";

            try {
                IDictionary<string, EmptyStruct> portDict = new Dictionary<string, EmptyStruct>();
                IList<string> envList = new List<string>();
                
                String imageName = root.GetProperty("imageName").ToString();
                
                
                Config parameters = new Config{
                    Image = imageName,
                    Env = envList,
                    ExposedPorts = portDict
                };

                await startContainer(imageName,parameters);
                rep = @"{""request"":""responseWorker"",""status"": true}";
            }
            catch(System.Exception e){
                Console.WriteLine("Un problème est survenu pendant le lancement de l'image: "+e.ToString());
                rep = @"{""request"":""responseWorker"",""status"": false}";
            }

            return rep;
        }


        private async Task<string> imageDL(JsonElement root){
            String rep = "";

            try
            {
                ImagesCreateParameters image = new ImagesCreateParameters{
                    FromImage = root.GetProperty("imageName").ToString()
                };
                await createContainer(image);
                rep = @"{""request"":""responseWorker"",""status"": true}";
                
            }
            catch (System.Exception e)
            {
                Console.WriteLine("Problème en téléchargeant l'image: " + e.ToString());
                rep = @"{""request"":""responseWorker"",""status"": false}";
            }

            return rep;
        }


        // PARTIE GESTION DOCKER

        async Task createContainer( ImagesCreateParameters image){
            await client.Images.CreateImageAsync(image, new AuthConfig(), new Progress<JSONMessage>(), CancellationToken.None);
        }

        async Task<bool> startContainer(string imageName, Config parameters){
            // On va d'abbord creer un conteneur avec les bons paramètres
            CreateContainerResponse response = await client.Containers.CreateContainerAsync(new CreateContainerParameters(parameters));
            
            //Et ensuite lancer ce qu'on a créé
            bool status = await client.Containers.StartContainerAsync(response.ID, new ContainerStartParameters(),CancellationToken.None);
            return status;
        }
    }   

}





