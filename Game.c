#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

typedef struct{
    float angulovisada;
    float angulolancamento;
    float veloinicial;
    int pnt;
}catapulta;

typedef struct{
    float x;
    float y;
    float raio;
    int pnt;
}alvo;

float conv_rad(float ang){
    float angrad;

    angrad = (ang*M_PI)/180;

    return angrad;
}


int pontuacao(float distancia, catapulta **player1, alvo **player2){
    if (distancia==0){

        (*player1)->pnt += 1000;

    } else if (distancia>0 && distancia<=1){

        (*player1)->pnt += 500;
        (*player2)->pnt += 500;

    } else if (distancia>1 && distancia<=3){

        (*player1)->pnt += 100;
        (*player2)->pnt += 200;

    } else if (distancia>2 && distancia<=5){

        (*player1)->pnt += 100;
        (*player2)->pnt += 300;

    } else if (distancia>5){

        (*player2)->pnt += 500;

    }

}

void getAlvo(alvo **player2){
    system("cls");
    //////////////////
    printf("Insira a coordenada X do alvo:\n");
    scanf("%f", &(*player2)->x);

    printf("Insira a coordenada Y do alvo:\n");
    scanf("%f", &(*player2)->y);

    printf("Insira o raio do alvo:\n");
    scanf("%f", &(*player2)->raio);
}

void getCatapulta(catapulta **player1){
    system("cls");
    //////////////////
    printf("Insira o angulo de visada:\n");
    scanf("%f", &(*player1)->angulovisada);

    printf("Insira o angulo de lancamento:\n");
    scanf("%f", &(*player1)->angulolancamento);

    printf("Insira a velocidade inicial:\n");
    scanf("%f", &(*player1)->veloinicial);

}

int main(void){

    int jogadas, i;
    float cordx, cordy, alcance, angrad;

    float x, y, distancia, d1,d2;
    //////////////////
    catapulta *player1;
    alvo *player2;
    player1 = (catapulta*) calloc(1, sizeof(catapulta));
    player2 = (alvo*) calloc(1, sizeof(alvo));
    //////////////////
    //Inicializando a Pontuação
    player1->pnt=0;
    player2->pnt=0;


    printf("                                    Let's play a game!!!                                       \n");

    printf("Insira o numero de jogadas:\n");

    if(scanf("%d", &jogadas) == 0){
        //printf("Insira um numero\n");
        //system("pause");
    }
    system("cls");

    for(i=1; i<jogadas+1; i++){
        printf("RODADA: %d", i);
        printf("\n[DIGITE ENTER PARA CONTINUAR]");
        getch();


        getCatapulta(&player1);
        while(player1->angulovisada > 45 || player1->angulovisada < -45)
        {
            system("cls");
            printf("\nERRO! Digite um valor valido para a catapulta.\n\nVALORES VALIDOS:\n45 >= ANGULO DE VISADA >= -45\n\n[DIGITE ENTER PARA CONTINUAR]");
            getch();
            getCatapulta(&player1);
        }


        getAlvo(&player2);
        while(player2->x < 150 || player2->x > 450 || player2->y < 0 || player2->y > 300 || player2->raio <= 0)
        {
            system("cls");
            printf("\nERRO! Digite um valor valido para o alvo.\n\nVALORES VALIDOS:\n150 < X < 450\n0 < Y < 300\nRaio > 0 \n\n[DIGITE ENTER PARA CONTINUAR]");
            getch();
            getAlvo(&player2);
        }
        system("cls");

        //CALCULO COORDENADAS/

        cordx=(pow(player1->veloinicial, 2)*(sin(2*conv_rad(player1->angulolancamento)))*cos(conv_rad(player1->angulovisada)))/9.8;
        cordy=((pow(player1->veloinicial, 2)*(sin(2*conv_rad(player1->angulolancamento)))*sin(conv_rad(player1->angulovisada)))/9.8) + 150;

        printf("\nCOORDENADA X: %.2f", cordx);
        printf("\nCOORDENADA Y: %.2f", cordy);

        d1 = player2->x - cordx;
        d2 = player2->y - cordy;

        //CALCULO DISTANCIA//

        distancia = sqrt(pow(d1,2) + pow(d2,2));
        printf("\nDISTANCIA: %f", distancia);
        printf("\n[DIGITE ENTER PARA CONTINUAR]");
        getch();

        distancia = distancia - player2->raio;
        if(distancia<0){
            distancia=0;
        }

        //PONTUACAO//
        pontuacao(distancia, &player1, &player2);

        system("cls");
    }

    printf("PONTUACAO FINAL:\n");
    printf("ATAQUE [%d] vs [%d] DEFESA", player1->pnt, player2->pnt);
    getch();
    return 0;

}
