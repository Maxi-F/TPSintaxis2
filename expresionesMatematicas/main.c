#include <stdio.h>
#include <stdlib.h>

int controlarExpresion(char *expresionTotal)
{
    char *aux = expresionTotal;
    while(*aux)
    {
        if(!(*aux >= '0' && *aux <= '9') && *aux != '+' && *aux != '-' && *aux != '*' && *aux != '/')
        {
            return 0;
        }
        *aux++;
    }
    return 1;
}

int encontrarNumero(char **expresion)
{
    int unNumero = 0, numeral = 1, signo = 1, i = 0;
    char *aux = *expresion;
    while(*aux && *aux != '*' && *aux != '/')
    {
        switch(*aux)
        {
            case '-':
                signo = signo*(-1);
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                unNumero = (unNumero * numeral) + (*aux - '0');
                numeral = numeral * 10;
                break;
            default:
                break;
        }
        *aux++;
        i++;
    }
    *expresion = *expresion + i;
    return unNumero;
}

int resolverExpresion(char *expresion)
{
    int unNumero = 0, otroNumero = 0, signo = 1, resultado;
    char *aux = expresion, operando;
    unNumero = encontrarNumero(&aux);
    while(*aux)
    {
        operando = *aux;
        *aux++;
        otroNumero = encontrarNumero(&aux);
        switch(operando)
        {
            case '/':
                unNumero = unNumero / otroNumero;
                break;
            case '*':
                unNumero = unNumero * otroNumero;
                break;
            default:
                break;
        }
    }
    return unNumero;
}

int resolverExpresionCompleta(char *expresionTotal, int *error)
{
    int expresionCorrecta = controlarExpresion(expresionTotal), resultado = 0;
    char *aux = expresionTotal;
        if(expresionCorrecta)
        {
            char matrizDeExpresiones[34][100] = {{}}; // En cada una de las posiciones "i" va a pertenecer un string con cada expresion matemotica a resolver.
            int i = 0, j = 0, cantidadDeExpresiones;
            while(*aux)
            {
                if(*aux != '+' && *aux != '-')
                {
                    matrizDeExpresiones[i][j] = *aux;
                    *aux++;
                    j++;
                }
                else
                {
                    if(j == 0 || matrizDeExpresiones[i][j-1] == '*' || matrizDeExpresiones[i][j-1] == '/' || matrizDeExpresiones[i][j-1] == '+' || matrizDeExpresiones[i][j-1] == '-')
                    {
                        matrizDeExpresiones[i][j] = *aux;
                        *aux++;
                        j++;
                    }
                    else
                    {
                        matrizDeExpresiones[i][j] = '\0';
                        matrizDeExpresiones[i+1][0] = *aux;
                        matrizDeExpresiones[i+1][1] = '\0';
                        *aux++;
                        j = 0;
                        i = i + 2;
                    }
                }
            }
            cantidadDeExpresiones = i + 1;
            i = 0;
            int resolucionUnaExpresion, resolucionOtraExpresion;
            if(cantidadDeExpresiones == 1) resultado = resolverExpresion(matrizDeExpresiones[i]);
            else
            {
                resolucionUnaExpresion = resolverExpresion(matrizDeExpresiones[i]);
                while(i < cantidadDeExpresiones)
                {
                    resolucionOtraExpresion = resolverExpresion(matrizDeExpresiones[i+2]);
                    switch(matrizDeExpresiones[i+1][0])
                    {
                        case '+':
                            resolucionUnaExpresion += resolucionOtraExpresion;
                            break;
                        case '-':
                            resolucionUnaExpresion -= resolucionOtraExpresion;
                            break;
                        default:
                            break;
                    }
                    i = i+2;
                }
                resultado = resolucionUnaExpresion;
            }
        }
        else
        {
            *error = 1;
            return 0;
        }
    *error = 0;
    return resultado;
}

int main()
{
    char expresionTotal[100];
    int resultado, error = 0;
    printf("Ingrese la expresion a resolver: ");
    scanf("%s", expresionTotal);
    resultado = resolverExpresionCompleta(expresionTotal, &error);
    if(error) printf("ERROR: la expresion ingresada no es valida.\n");
    else printf("\n el resultado es: %d", resultado);
    return 0;
}
