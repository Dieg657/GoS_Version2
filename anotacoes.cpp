/*
time_t tempo;
struct tm a = {0};
a.tm_hour = 14;
a.tm_min = 48;
a.tm_sec = 0;
a.tm_year = 118;
a.tm_mon = 2;
a.tm_mday = 31;

time(&tempo);

double seconds = difftime(tempo, mktime(&a));
long long aux;
for (int i = 0; seconds < 60; i++) {
   usleep(1000);
   time(&tempo);
   seconds = difftime(tempo, mktime(&a));
   printf("%.f seconds\n", seconds);
   printf("%d quantidade de operações dentro do segundo", i);
}
printf ("%.f seconds", seconds);
*/

/*
    time_t now = time(NULL);
    struct tm tempo1 = *localtime(&now);
    struct tm tempo2 = tempo1;
    tempo2.tm_sec += 70;
    int sec = 0;
    double aux;

    time(&now);
    aux = difftime(now,mktime(&tempo2));
    for (int i = 0; difftime(mktime(&tempo2),now) > 0; i++) {


        if(aux != difftime(now,mktime(&tempo2))){
            sec++; aux = difftime(now,mktime(&tempo2));
        }
        //printf("%f diferença\n",difftime(now,mktime(&tempo2)));
        printf("%d segundos passados!\n", sec);
        time(&now);
    }
    cout << "Tempo inicial que começou a simulação: " << asctime(&tempo1);

    cout << "Tempo final (limite): " << asctime(&tempo2) << endl;

*/


/*
    const int nrolls = 20000; // number of experiments
    const int nstars = 300;   // maximum number of stars to distribute

    std::default_random_engine generator;
    std::poisson_distribution<int> distribution(15);

    int p[30]={};

    for (int i=0; i<nrolls; ++i) {
      int number = distribution(generator);
      if (number<30) ++p[number];
      //cout << number << "; ";
    }

    std::cout << "poisson_distribution (mean=15):" << std::endl;
    for (int i=0; i<30; ++i)
      std::cout << i << ": " << std::string(p[i]*nstars/nrolls,'*') << std::endl;
*/

/*
    const int nrolls = 1000; // number of experiments
    const int nstars = 300;   // maximum number of stars to distribute

    std::default_random_engine generator;
    std::poisson_distribution<int> distribution(15);

    int p[30]={};

    for (int i=0; i<nrolls; ++i) {
      int number = distribution(generator);
      if (number<30) ++p[number];
      //cout << number << "; ";
    }

    std::cout << "poisson_distribution (mean=15):" << std::endl;
    for (int i=0; i<30; ++i)
      std::cout << i << ": " << p[i] << std::endl;
*/

/*
    const int nrolls=10000;  // number of experiments
    const int nstars=100;    // maximum number of stars to distribute
    const int nintervals=11; // number of intervals

    std::default_random_engine generator;
    std::exponential_distribution<double> distribution(0.5);

    int p[nintervals]={};

    for (int i=0; i<nrolls; ++i) {
      double number = distribution(generator);
      if (number<1.0) {
          ++p[int(nintervals*number)];
          cout << "Posição do vetor: " << int(nintervals*number) << endl;
      }
    }

    std::cout << "exponential_distribution (3.5):" << std::endl;
    std::cout << std::fixed; std::cout.precision(1);

    for (int i=0; i<nintervals; ++i) {
      std::cout << float(i)/nintervals << "-" << float(i+1)/nintervals << ": ";
      std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
    }
*/
/*
    const int nrolls=10000;  // number of experiments
    const int nintervals=11; // intervalos de tempo

    std::default_random_engine generator;
    std::exponential_distribution<double> exponential_distribution(0.5);
                     //0 , 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    int p[nintervals]={56,57,58,59,60,61,62,63,64,65,66}; // Tempos de duração

    for (int i=0; i<nrolls; ++i) {
      double number = exponential_distribution(generator);
      if (number<1.0) {
          //cout << "Posição do vetor: " << int(nintervals*number) << endl;
          cout << "Segundos de duração da na via: " << p[int(nintervals*number)] << endl;
      }
    }
*/
