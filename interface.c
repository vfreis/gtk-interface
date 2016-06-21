#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

void on_btnCalcular_clicked(GtkButton *button);

double f1 (double ox);
double f2 (double cf);
double f3 (double ph);
double f4 (double dbo);
double f5 (double temp);
double f6 (double nt);
double f7 (double ft);
double f8 (double tu);
double f9 (double st);	
double calculo();

double fun[9], res[9], cf = 0, ph = 0, dbo = 0, nt = 0, ft = 0, temp = 0, tu = 0, st = 0, ox = 0, total = 0;
	
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkBuilder *builder;	
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "Unsaved.glade", NULL);
	GtkWindow *window = (GtkWindow*)gtk_builder_get_object(builder, "IQA");	

	//gtk_window_set_title(GtkWindow *window, "Indice de qualidade da agua");

	GtkButton *button = (GtkButton*)gtk_builder_get_object(builder, "btnCalcular");

	g_signal_connect(button, "clicked",
			G_CALLBACK(calculo), (gpointer)builder);
	
	gtk_widget_show((GtkWidget*)window);
	
	gtk_builder_connect_signals(builder, NULL );
	
	gtk_main();
}

double calculo(GtkButton *button, gpointer data)
{	

    GtkBuilder *builder = (GtkBuilder*) data;

    GtkEntry *entry1 = (GtkEntry*)gtk_builder_get_object(builder, "txtColiformes");
    GtkEntry *entry2 = (GtkEntry*)gtk_builder_get_object(builder, "txtPh");
	GtkEntry *entry3 = (GtkEntry*)gtk_builder_get_object(builder, "txtDbo");
	GtkEntry *entry4 = (GtkEntry*)gtk_builder_get_object(builder, "txtNitrogenio");
	GtkEntry *entry5 = (GtkEntry*)gtk_builder_get_object(builder, "txtFOsforo");
	GtkEntry *entry6 = (GtkEntry*)gtk_builder_get_object(builder, "txtTemperatura");
	GtkEntry *entry7 = (GtkEntry*)gtk_builder_get_object(builder, "txtTurbidez");
	GtkEntry *entry8 = (GtkEntry*)gtk_builder_get_object(builder, "txtOxigenio");
	GtkEntry *entry9 = (GtkEntry*)gtk_builder_get_object(builder, "txtSolidos");
	GtkEntry *entry10 = (GtkEntry*)gtk_builder_get_object(builder, "txtIqa");
	
    const char* valor_da_entry1 = gtk_entry_get_text(entry1);
    const char* valor_da_entry2 = gtk_entry_get_text(entry2);
	const char* valor_da_entry3 = gtk_entry_get_text(entry3);
	const char* valor_da_entry4 = gtk_entry_get_text(entry4);
	const char* valor_da_entry5 = gtk_entry_get_text(entry5);
	const char* valor_da_entry6 = gtk_entry_get_text(entry6);
	const char* valor_da_entry7 = gtk_entry_get_text(entry7);
	const char* valor_da_entry8 = gtk_entry_get_text(entry8);
	const char* valor_da_entry9 = gtk_entry_get_text(entry9);	
	// Entry do resultado

	cf = atof(valor_da_entry1);
	ph = atof(valor_da_entry2);
	dbo = atof(valor_da_entry3);
	nt = atof(valor_da_entry4);
	ft = atof(valor_da_entry5);
	temp = atof(valor_da_entry6);
	tu = atof(valor_da_entry7);
	st = atof(valor_da_entry8);
	ox = atof(valor_da_entry9);
	
	fun[0] = f1(ox);
    fun[1] = f2(cf);
    fun[2] = f3(ph);
    fun[3] = f4(dbo);
    fun[4] = f5(temp);
    fun[5] = f6(nt);
    fun[6] = f7(ft);
    fun[7] = f8(tu);
    fun[8] = f9(st);

    res[0] = pow(fun[0], 0.17);
    res[1] = pow(fun[1], 0.15);
    res[2] = pow(fun[2], 0.12);
    res[3] = pow(fun[3], 0.10);
    res[4] = pow(fun[4], 0.10);
    res[5] = pow(fun[5], 0.10);
    res[6] = pow(fun[6], 0.10);
    res[7] = pow(fun[7], 0.08);
    res[8] = pow(fun[8], 0.08);

    total = res[0] * res[1] * res[2] * res[3] * res[4] * res[5] * res[6] * res[7] * res[8];

 	char resultado[10];

 	sprintf(resultado, "%.0lf", total);

    GtkLabel *label15 = (GtkLabel*)gtk_builder_get_object(builder, "label15");

    GtkLabel *label3 = (GtkLabel*)gtk_builder_get_object(builder, "label3");
    gtk_label_set_text(label3, resultado);

    //char O[6] = "Otima", B[4] = "Boa", A[10] ="Aceitavel", R[5] ="Ruim", P[8]="Pessima";

    if(total > 80 && total <= 100){
    	printf("KG1\n");
 		gtk_label_set_text(label15, "Otima");
 	}
 	else if(total >50 && total <= 80){
    	printf("KG2\n");
 		gtk_label_set_text(label15, "Boa");
 	}
 	else if(total > 36 && total <= 50){
    	printf("KG3\n");
 		gtk_label_set_text(label15, "Aceitavel");
 	}
 	else if(total > 20 && total <= 36){
    	printf("KG4\n");
 		gtk_label_set_text(label15, "Razoalvel");
 	}
 	else if(total <= 20){
    	printf("KG5\n");
 		gtk_label_set_text(label15, "Pessima");
 	}
}

double f1 (double ox) //Função da oxigênio dissolvido
{
	double a = 100.8, b = -106.0, c = -3745.0, f1 = 0;

    f1 = a * exp (pow((ox + b), 2)/ c);

    return f1;
}

double f2 (double cf) //Coliformes fecais
{
	double f2 = 0;

	f2 = 98.24034 - 34.7145 * (log10(cf)) + 2.614267 * (pow(log10(cf), 2)) + 0.107821 * (pow(log10(cf), 3));

	return f2;
}

double f3 (double ph) //Potencial Hidrogeniônico
{
	double f3 = 0;

    if(ph <= 2){
 		f3 = 1;
 	    }
 	    else if(ph > 2 && ph <= 6.9){
 		    f3 = -37.1085 + 41.91277 * ph - 15.7043 * pow(ph, 2) + 2.417486 * pow(ph, 3) - 0.091252* pow(ph, 4);
 	    }
 	    else if(ph > 6.9 && ph <= 7.1){
 		    f3 = -4.69365 - 21.4593 * ph - 68.4561 * pow(ph, 2) + 21.638886 * pow(ph, 3) - 1.59165 * (ph, 4);
 	    }
 	    else if(ph> 7.1 && ph <=12){
 		    f3 = -7698.19 + 3262.031 * ph - 499.494 * pow(ph, 2) + 33.1551* pow(ph, 3) - 0.810613 * pow(ph, 4);
 	    }
 	    else{
 		    f3 = 3;
 	    }

    return f3;
}

double f4 (double dbo) //Demanda Bioquimica de Oxigenio
{
	double f4 = 0;

    if(dbo > 30){
 		f4 = 2;
 	}
 	else{
 		f4 = 100.9571 - 10.7121 * dbo + 0.49544 * pow(dbo, 2) - 0.011167 * pow(dbo, 3) + 0.0001 * pow(dbo, 4);
 	}

	return f4;
}

double f5 (double temp) //Variação de temperatura
{
	double f5 = 0;

    if(temp > 15){
 		f5 = 9;
 	}
 	else if(temp <= 5){
 		f5 = 1;
 	}
 	else{
 		f5 = 1/(0.0003869*pow(temp + 0.1815, 2) + 0.01081);
 	}

    return f5;
}

double f6 (double nt) //Nitrogenio Total
{
	double f6 = 0;

    if(nt <= 10){
 		f6 = -5.1 * nt + 100.17;
 	}
 	else if(nt > 10 && nt <= 60){
 		f6 = -22.853 * log(nt) + 101.18;
 	}
 	else if(nt > 60 && nt <= 90){
 		f6 = 10000000000 * pow(nt, -5.1161);
 	}
 	else if(nt > 90){
 		f6 = 1;
 	}

    return f6;
}

double f7 (double ft) //Fosforo Total
{
	double f7 = 0;

    if(ft > 10){
 		f7 = 5;
 	}
 	else{
 		f7 = 79.7 * (pow(ft + 0.821, -1.15));
 	}

    return f7;
}

double f8 (double tu) //Turbidez
{
	double f8 = 0;

    if(tu > 100){
 		f8 = 5;
 	}
 	else{
 		f8 = 90.37 * pow(2.7182818, (-0.0169 * tu)) - 15 * cos((0.0571 * (tu-30))) + 10,22 * pow(2.718281828, (-0.231*tu)) -0.8;
 	}

    return f8;
}

double f9 (double st) //Solidos totais
{
	double f9 = 0;

   	if(st > 500){
 		f9 = 30;
 	}
 	else{
 		f9 = 133.17 * (pow(2.7182818, (-0.0027 * st))) -53.17 * (pow(2.7182818 , (-0.0141 * st))) + ((-6.2 * (pow(2.7182818, (-0.00462*st)))) * sin(0.0146 * st));

 	}

    return f9;
}
