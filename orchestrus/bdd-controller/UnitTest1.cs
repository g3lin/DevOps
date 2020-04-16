using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace bdd_controller
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void CommInvalde()
        {
            Program pr = new Program();
            string repAtt = @"{""request"":""responseDB"",""status"":false}";
            Assert.IsTrue(pr.parseCommand("invalide").Equals(repAtt));
        }

    }
}
