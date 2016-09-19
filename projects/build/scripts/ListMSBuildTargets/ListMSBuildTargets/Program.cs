using System;
using Microsoft.Build.Evaluation;

class Program
{
    static void Main(string[] args)
    {
        Project project = new Project(args[0]);
        foreach (string target in project.Targets.Keys)
        {
            Console.WriteLine("{0}", target);
        }
    }
}