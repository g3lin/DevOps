using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace worker
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            Program pr = new Program();
            Assert.IsTrue(pr.parseCommand("{\"request\":\"invalid\"}").Equals(""));
        }
    }
}
