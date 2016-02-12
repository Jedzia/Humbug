int main(int ac, char* av[]) {
    ProgOptions progOpts(ac, av);

    if ( progOpts.isHelpRequested() )
        return 0;

    if ( !progOpts.isValid() ) {
        cout << "Program-Options error[" << progOpts.getResult() << "].\n";
        return 1;
    }

    ProcessProject::Options &poptions = progOpts.getPoptions();
    ProcessProject pp(&poptions);
    pp.run();
}
