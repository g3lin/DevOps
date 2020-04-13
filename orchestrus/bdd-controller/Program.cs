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
            SocketsManager sock = new SocketsManager(main);
            sock.StartListening();

        }

        private void Main(){

            string pgPassword = Environment.GetEnvironmentVariable("POSTGRES_PASSWORD");
            var connString = "Host=postgres_container;Username=postgres;Password="+pgPassword+";Database=IGL601";
            conn = new NpgsqlConnection(connString);

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
                
                else if(request.ToString().Equals("DBLisrWorkers"))
                    rep = DBListWorkers(root);
                
                else if(request.ToString().Equals("DBUpdateImage"))
                    rep = DBUpdateImage(root).ToString();
                
                else if(request.ToString().Equals("DBUpdateWorker"))
                    rep = DBUpdateWorker(root).ToString();

                

            }
            catch (System.Exception)
            {
                
                throw;
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

            NpgsqlCommand cmd = new NpgsqlCommand("SELECT some_field FROM data", conn);
            var reader = cmd.ExecuteReader();
            reader.Read();
            return reader.GetString(0);
        
        }


        private string DBListWorkers(JsonElement root){

            NpgsqlCommand cmd = new NpgsqlCommand("SELECT * FROM worker WHERE", conn);
            var reader = cmd.ExecuteReader();
            reader.Read();
            return reader.GetString(0);
        
        }


        private bool DBUpdateImage(JsonElement root){
           
            var cmd = new NpgsqlCommand("INSERT INTO data (some_field) VALUES (@p)", conn);
            cmd.Parameters.AddWithValue("p", "Hello world");
            int ret = cmd.ExecuteNonQuery();
            
            if (ret == -1 || ret == 0) return false;
            else return true;    
        
        }

        private bool DBUpdateWorker (JsonElement root){

            var cmd = new NpgsqlCommand("INSERT INTO data (some_field) VALUES (@p)", conn);
            cmd.Parameters.AddWithValue("p", "Hello world");
            int ret = cmd.ExecuteNonQuery();
            
            if (ret == -1 || ret == 0) return false;
            else return true;
        
        }

    }
}
