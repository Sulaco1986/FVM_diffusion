#include <stdio.h>
#include <stdlib.h>

void get_matrix (double **a, int n, double Ae, double Aw, double EAp, double WAp, double Sp, double Ap);
void boundary_vector (double *b, int n, double K, double A, double dx, double Ta, double Tb);
void print_matrix (double **a, int n);
void row_ops (double **a, double *b, int n);
void back_sub (double **a, double *b, double *x, int n);


int main ()

{
	int i, j, n;
	double **a, *b, *x, *p, Ta, Tb, A, K, L, dx, Ae, Aw, Ap, Sp, EAp, WAp;
	
	
	// Get inputs //
	
	printf("Please enter the length of the rod (m)...\n");
	scanf("%lf", &L);
	printf("Please enter the cross-sectional area (m^3)...\n");
	scanf("%lf", &A);
	printf("Please enter the number of nodes to be used...\n");
	scanf("%d", &n);
	printf("Please enter the first end temperature...\n");
	scanf("%lf", &Ta);
	printf("Please enter the last end temperature...\n");
	scanf("%lf", &Tb);
	printf("Please enter the thermal conductivity of the material (W/m.K)...");
	scanf("%lf", &K);
	
	
	
	// Ae Aw Sp
	dx = L/n;
	
	Ae = (K/dx)*A; //100
	Aw = (K/dx)*A; //100
	Sp = -(2*K*A)/dx; //200
	Ap = Aw + Ae;
	EAp = Aw - Sp; 
	WAp	= Ae - Sp; 
	
	// Memory allocation //
	// Memory allocation for 'a' matrix //
	
	a = (double **) malloc (n * sizeof(double *));
	for (j = 0; j < n; j++)
		a[j] = (double *) malloc (n * sizeof(*a));
	
	// Memory allocation for 'b' vector //
	
	b = (double *) malloc (n * sizeof(double));
	
	// Memory allocation for 'x' vector (solution vector) //
	
	x = (double *) malloc  (n * sizeof(double));
	
	// Memory allocation for 'p' vector (mirroring coefficient) //
	
	p = ( double *)	malloc (n * sizeof(double));
	
	// Function calls //
	
	get_matrix (a, n, Ae, Aw, EAp, WAp, Sp, Ap);
	boundary_vector (b, n, K, A, dx, Ta, Tb);
	print_matrix (a, n);
	printf("\n");
	row_ops (a, b, n);
	printf("\n");
	print_matrix (a, n);
	back_sub (a, b, x, n);
	printf("\n");
	
	
	for (i=0; i<n; i++)
		{
			printf("\n%.2f, ", x[i]);
		}
			
	return 0;
	
}

void get_matrix (double **a, int n, double Ae, double Aw, double EAp, double WAp, double Sp, double Ap)
{
	int i, j;
	
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			if (i == j)
			{
				if (i == 0)
					a[i][j] = (WAp);
				else if (i == n-1)
					a[i][j] = (EAp);
				else
					a[i][j] = (Ap);
			}	
			
			else if (i == j-1)
			{
				a[i][j] = -Ae;
			}
			else if (i == j+1)
			{
				a[i][j] = -Aw;
			}
		}
	}
}

void print_matrix (double **a, int n)
{
	int i, j;
	
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			printf("%.2f, ", a[i][j]);
		}
		printf("\n ");
	}
}

void boundary_vector (double *b, int n, double K, double A, double dx, double Ta, double Tb)
{
	int i;
	
	double Su;
	
	Su = (2*K*A)/dx;
	
	for (i=0; i<n; i++)
	{
		if (i == 0)
		{
			b[i] = Su*Ta;
		}
		else if (i == n-1)
		{
			b[i] = Su*Tb;
		}
		else
		{
			b[i] = 0;
		}
	printf("\n%.2f, ", b[i]);	
	}
	printf("\n" "\n");
}

void row_ops (double **a, double *b, int n)
{
	int i, j, k; 
	double p;
	
	for (k=0; k<n; k++)
		for (i=k+1; i<n; i++)
		{
			p=a[i][k]/a[k][k];
			for (j=0; j<n; j++)
				{
				a[i][j] -= p*a[k][j];
				}
			b[i] -= p*b[k];
			
		printf("\n%.2f, ", p);	
		}
	printf("\n ");
		
}

void back_sub (double **a, double *b, double *x, int n)
{
	double Sum;
	int i, j;
	
	for (i=n-1; i>=0; i--)
	{
		Sum = 0;
		x[i] = 0;
	
		
		for (j=i; j<n; j++)
			Sum += a[i][j]*x[j];
		x[i]=(b[i]-Sum)/a[i][i];
		
	}
}
