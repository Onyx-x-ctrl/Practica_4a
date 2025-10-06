struct dupla_int {
    double a;
    double b;
};

program CALC_PROG {
    version CALC_VERS {
        double SUMA(dupla_int) = 1;
        double RESTA(dupla_int) = 2;
        double MULTIPLICACION(dupla_int) = 3;
        double DIVISION(dupla_int) = 4;
    } = 1;
} = 0x41111111;
