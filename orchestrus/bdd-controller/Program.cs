using System;
using Npgsql;
using System.Text.Json;

namespace bdd_controller
{
    public class Program
    {

        private NpgsqlConnection conn;

        static void Main(string[] args)
        {
            
            Program main = new Program();
            main.Main();
            SocketsManager sock = new SocketsManager(main);
            sock.StartListening();

        }

        private void Main(){

            string pgPassword = Environment.GetEnvironmentVariable("POSTGRES_PASSWORD");
            var connString = "Host=postgres_container;Username=postgres;Password="+pgPassword+";Database=IGL601";
            try {
                conn = new NpgsqlConnection(connString);
                conn.Open();
                Console.WriteLine("Etat de la connection BDD: "+conn.State.ToString());
            }
            catch (System.Exception){
                Console.WriteLine("Erreur lors de la connexion à la BDD PostgreSQL");
                Environment.Exit(1);

            }
            

        }



        public string parseCommand(string content){
            string rep = "";
            try
            {
                JsonDocument document = JsonDocument.Parse(content);
                JsonElement root = document.RootElement;
                JsonElement request = root.GetProperty("request");

                if(request.ToString().Equals("DBListImages"))
                    rep = DBListImages(root);
                
                else if(request.ToString().Equals("DBListWorkers"))
                    rep = DBListWorkers(root);
                
                else if(request.ToString().Equals("DBUpdateImage"))
                    rep = DBUpdateImage(root).ToString();
                
                else if(request.ToString().Equals("DBUpdateWorker"))
                    rep = DBUpdateWorker(root).ToString();
                else{
                    throw new Exception("requete malformée");
                }

                

            }
            catch (System.Exception e)
            {
                Console.WriteLine("une erreur est survenue dans la BDD:"+e.ToString());
                rep = @"{""request"":""responseDB"",""status"":false}";
            }

            return rep;
        }


        private string DBListImages(JsonElement root){
            // await using (var cmd = new NpgsqlCommand("SELECT some_field FROM data", conn))
            // await using (var reader = await cmd.ExecuteReaderAsync()){
            //     while (await reader.ReadAsync())
            //         Console.WriteLine(reader.GetString(0));   
            //     return reader.GetString(0);
            // }

            using(NpgsqlCommand cmd = new NpgsqlCommand("SELECT * FROM image WHERE worker_ip = @wip ;", conn)){
                cmd.Parameters.AddWithValue("wip", root.GetProperty("ipWorker").ToString());
                using(var reader = cmd.ExecuteReader()){
                    reader.Read();
                    return reader.GetString(0);
                }
            }
        
        }


        private string DBListWorkers(JsonElement root){

            using( NpgsqlCommand cmd = new NpgsqlCommand("SELECT * FROM worker;", conn)){
                using (var reader = cmd.ExecuteReader()){
                    reader.Read();
                    return reader.GetString(0);
                }
            }
        
        }


        private bool DBUpdateImage(JsonElement root){
           
            using (var cmd = new NpgsqlCommand("INSERT INTO image (name, docker_id, worker_ip, worker_port, image_ports)"+
                                        " VALUES (@name, @dID, @wIP, @wPort, @imPorts);", conn)){
           
                cmd.Parameters.AddWithValue("name", root.GetProperty("nomImage").ToString());
                cmd.Parameters.AddWithValue("dID", root.GetProperty("idImage").ToString());
                cmd.Parameters.AddWithValue("wIP", root.GetProperty("ipWorker").ToString());
                cmd.Parameters.AddWithValue("wPort", root.GetProperty("workerPort").ToString());
                cmd.Parameters.AddWithValue("imPorts", root.GetProperty("ImagePorts").ToString());

                
                int ret = cmd.ExecuteNonQuery();
                
                if (ret == -1 || ret == 0) return false;
                else return true;   
            } 
        
        }

        private bool DBUpdateWorker (JsonElement root){

            using (var cmd = new NpgsqlCommand("INSERT INTO worker (ip, port, status) VALUES (@ip, @port, @status)"+
                                        "", conn)){
                
                cmd.Parameters.AddWithValue("ip", root.GetProperty("ip").ToString());
                cmd.Parameters.AddWithValue("port", root.GetProperty("workerPort").ToString());
                cmd.Parameters.AddWithValue("status", root.GetProperty("status").ToString().Equals("true"));

                int ret = cmd.ExecuteNonQuery();
                
                if (ret == -1 || ret == 0) return false;
                else return true;
            }
        
        }

    }
}
