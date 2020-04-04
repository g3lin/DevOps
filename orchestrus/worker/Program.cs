using System;

using Docker.DotNet;
using Docker.DotNet.Models;

using System.Net;  
using System.Net.Sockets;  
using System.Text;  
using System.Threading.Tasks;
using System.Threading;

using System.IO;


/**

On va utiliser le SDK de docker en C# par MS
https://github.com/microsoft/Docker.DotNet

**/

namespace worker
{
    class Program
    {
        static async Task Main(string[] args)
        {
            // Création du client Docker
            DockerClient client = new DockerClientConfiguration(
                new Uri("unix:///var/run/docker.sock"))
            .CreateClient();

            SocketsManager socket = new SocketsManager();
            SocketsManager.StartListening();

            // Pull de l'image
            ImagesCreateParameters image = new ImagesCreateParameters
            {
                FromImage = "hello-seattle",
                Tag = "linux",
            };
            await createContainer(client, image);
            bool status = await startContainer(client, "hello-world", new string[0]);
            Console.WriteLine(status.ToString());
        }

        public static string parseCommand(string content){
            string rep = "";

            return content;
        }



        static async Task createContainer(DockerClient client, ImagesCreateParameters image){
            await client.Images.CreateImageAsync(image, new AuthConfig(), new Progress<JSONMessage>(), CancellationToken.None);
        }

        static async Task<bool> startContainer(DockerClient client, string imageName, string[] dockerParams){
            // On va d'abbord creer un conteneur avec les bons paramètres
            var parameters = new Config {
              Image = imageName,              
              ArgsEscaped = false,
              AttachStderr = false,
              AttachStdin = false,
              AttachStdout = true,
              Cmd = dockerParams
            };
            CreateContainerResponse response = await client.Containers.CreateContainerAsync(new CreateContainerParameters(parameters));
            
            //Et ensuite lancer ce qu'on a créé
            bool status = await client.Containers.StartContainerAsync(response.ID, new ContainerStartParameters(),CancellationToken.None);
            return status;
        }
    }   

}





