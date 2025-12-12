#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct route
{
char startpoint[50];
int length;
int altup;
int altdown;
int altmax;
int altmin;
char endpoint[50];
};

int estimatedTime(int l, int up)
{
  float ft;
  int t;
  ft = (float)l/65.0+(float)up/10.0;
  if ((int)(ft+0.5)==(int)ft)
    t = (int)ft;
  else
    t = (int)ft+1;

  return t;
}

float floatTime(int l, int up)
{
  return (1.0)*l/65.0+(1.0)*up/10.0;
}

int roundup(int n)
{
  if ((int)(n+0.5)==(int)n)
    return (int)n;
  else
    return (int)(n+1);
}

struct route *readFromInput(int *n)
{
  int m;
  struct route *A;
  scanf("%d", &m);
  A = (struct route *)malloc(m*sizeof(struct route));
  for (int i=0;i<m;i++)
    {
      scanf(" ");
      fgets(A[i].startpoint, 50, stdin);
      A[i].startpoint[strcspn(A[i].startpoint, "\n")]='\0';
      /*scanf("%d %d %d %d %d", &A[i].length, &A[i].altup, &A[i].altdown, &A[i].altmax, &A[i].altmin);*/
      scanf("%d", &A[i].length);
      scanf("%d", &A[i].altup);
      scanf("%d", &A[i].altdown);
      scanf("%d", &A[i].altmax);
      scanf("%d", &A[i].altmin);
      scanf(" ");
      fgets(A[i].endpoint, 50, stdin);
      A[i].endpoint[strcspn(A[i].endpoint, "\n")]='\0';
    }
  *n=m;
  return A;
}

void printRoute(struct route r, int t)
{
  printf("From %s to %s\n", r.startpoint, r.endpoint);
  printf("Uphill %d, Downhill %d\n", r.altup, r.altdown);
  printf("Max altitude %d, Min altitude %d\n", r.altmax, r.altmin);
  printf("Length %d, Estimated time %d min\n", r.length, t);
  printf("\n");
}

void printRouteReturn(struct route r, int t)
{
  printf("From %s to %s\n", r.endpoint, r.startpoint);
  printf("Uphill %d, Downhill %d\n", r.altdown, r.altup);
  printf("Max altitude %d, Min altitude %d\n", r.altmax, r.altmin);
  printf("Length %d, Estimated time %d min\n", r.length, t);
  printf("\n");
}

void printData(struct route *A, int n)
{
  int i, j, total_time;
  struct route temp;
  //A = (struct route *)malloc(n*sizeof(struct route));
  for (i=1;i<n;i++)
    for (j=n;j>=i;j--)
      {
        if (A[j-1].length<A[j].length)
        {
          temp=A[j-1];
          A[j-1]=A[j];
          A[j]=temp;
        }
      }
  for (i=0;i<n;i++)
    {
      total_time = estimatedTime(A[i].length, A[i].altup);
      printRoute(A[i],total_time);
      /*printf("From %s to %s\n", A[i].startpoint, A[i].endpoint);
      printf("Uphill %d, Downhill %d\n", A[i].altup, A[i].altdown);
      printf("Max altitude %d, Min altitude %d\n", A[i].altmax, A[i].altmin);
      printf("Length %d, Estimated time %d", A[i].length, total_time);
      printf("\n");*/
      if (strcmp(A[i].startpoint, A[i].endpoint)!=0)
      {
        total_time = estimatedTime(A[i].length, A[i].altdown);
        printRouteReturn(A[i],total_time);
        /*printf("From %s to %s\n", A[i].endpoint, A[i].startpoint);
        printf("Uphill %d, Downhill %d\n", A[i].altdown, A[i].altup);
        printf("Max altitude %d, Min altitude %d\n", A[i].altmax, A[i].altmin);
        printf("Length %d, Estimated time %d", A[i].length, total_time);
        printf("\n");*/
      }
    }
}

void findShort(struct route *A, int n)
{
  int i,j,t_t, L;
  struct route temp;
  //A=(struct route *)malloc(n*sizeof(struct route));
  for (i=1;i<n;i++)
    for (j=n;j>=i;j--)
      {
        if (A[j-1].length<A[j].length)
        {
          temp=A[j-1];
          A[j-1]=A[j];
          A[j]=temp;
        }
      }

  scanf("%d", &L);

  for (i=0;i<n;i++)
    {
      if (A[i].length<=L)
      {
        t_t = estimatedTime(A[i].length, A[i].altup);
        printRoute(A[i],t_t);
        /*printf("From %s to %s\n", A[i].startpoint, A[i].endpoint);
        printf("Uphill %d, Downhill %d\n", A[i].altup, A[i].altdown);
        printf("Max altitude %d, Min altitude %d\n", A[i].altmax, A[i].altmin);
        printf("Length %d, Estimated time %d\n", A[i].length, total_time);*/

        if (strcmp(A[i].startpoint, A[i].endpoint)!=0)
        {
          t_t = estimatedTime(A[i].length, A[i].altdown);
          printRouteReturn(A[i],t_t);
          /*printf("From %s to %s\n", A[i].endpoint, A[i].startpoint);
          printf("Uphill %d, Downhill %d\n", A[i].altdown, A[i].altup);
          printf("Max altitude %d, Min altitude %d\n", A[i].altmax, A[i].altmin);
          printf("Length %d, Estimated time %d", A[i].length, total_time);
          printf("\n");*/
        }
      }
    }
}

void findLocation(struct route *A, int n)
{
  char *loc;
  int i,j,t;
  loc = (char *)malloc(50*sizeof(char));
  fgets(loc,50,stdin);
  loc[strcspn(loc, "\n")]='\0';
  loc = (char *)realloc(loc, (strlen(loc)+1)*sizeof(char));
  struct route temp;
  //A=(struct route *)malloc(n*sizeof(struct route));
  for (i=1;i<n;i++)
    for (j=n;j>=i;j--)
      {
        if (A[j-1].length<A[j].length)
        {
          temp=A[j-1];
          A[j-1]=A[j];
          A[j]=temp;
        }
      }

  for (i=0;i<n;i++)
    {
      if (strcmp(A[i].startpoint, loc)==0)
      {
        t = estimatedTime(A[i].length, A[i].altup);
        printRoute(A[i],t);
      }
      else
      {
        if (strcmp(A[i].endpoint,loc)==0)
        {
          t = estimatedTime(A[i].length, A[i].altdown);
          printRouteReturn(A[i],t);
        }
      }
    }
}

void findUpHill(struct route *A, int n)
{
  int i,j,t;
  struct route temp;
  //A=(struct route *)malloc(sizeof(struct route));
  for (i=1;i<n;i++)
    for (j=n;j>=i;j--)
      {
        if (A[j-1].length<A[j].length)
        {
          temp=A[j-1];
          A[j-1]=A[j];
          A[j]=temp;
        }
      }

  for (i=0;i<n;i++)
    {
      if (A[i].altup>A[i].altdown)
      {
        t = estimatedTime(A[i].length,A[i].altup);
        printRoute(A[i],t);
      }
      else
      {
        if (A[i].altup<A[i].altdown)
        {
          t = estimatedTime(A[i].length,A[i].altdown);
          printRouteReturn(A[i],t);
        }
      }
    }
}

void findDownHill(struct route *A, int n)
{
  int i,j,t;
  struct route temp;
  //A=(struct route *)malloc(sizeof(struct route));
  for (i=1;i<n;i++)
    for (j=n;j>=i;j--)
      {
        if (A[j-1].length<A[j].length)
        {
          temp=A[j-1];
          A[j-1]=A[j];
          A[j]=temp;
        }
      }

  for (i=0;i<n;i++)
    {
      if (A[i].altup<A[i].altdown)
      {
        t = estimatedTime(A[i].length,A[i].altup);
        printRoute(A[i],t);
        
      }
      else
      {
        if (A[i].altup>A[i].altdown)
        {
          t = estimatedTime(A[i].length,A[i].altdown);
          printRouteReturn(A[i],t); 
        }
      }
    }
}

void findAltitude(struct route *A, int n)
{
  int i,j,t;
  struct route temp;
  //A=(struct route *)malloc(n*sizeof(struct route));
  for (i=1;i<n;i++)
    for (j=n;j>=i;j--)
      {
        if (A[j-1].length<A[j].length)
        {
          temp=A[j-1];
          A[j-1]=A[j];
          A[j]=temp;
        }
      }

  int min,max;
  scanf("%d %d", &min, &max);

  for (i=0;i<n;i++)
    {
      if (A[i].altmin>=min && A[i].altmax<=max)
      {
        t=estimatedTime(A[i].length,A[i].altup);
        printRoute(A[i],t);
        if (strcmp(A[i].startpoint, A[i].endpoint)!=0)
        {
          t=estimatedTime(A[i].length,A[i].altdown);
          printRouteReturn(A[i],t);
        }
      }
    }
}

void findTimely(struct route *A, int n)
{
  int i,j,T;
  float t1,t2,ft;
  struct route temp;
  //A=(struct route *)malloc(n*sizeof(struct route));
  for (i=1;i<n;i++)
    for (j=n;j>=i;j--)
      {
        if (A[j-1].length<A[j].length)
        {
          temp=A[j-1];
          A[j-1]=A[j];
          A[j]=temp;
        }
      }

  scanf("%d", &T);

  ft = (float)T;

  for (i=0;i<n;i++)
    {
      t1=floatTime(A[i].length,A[i].altup);
      t2=floatTime(A[i].length,A[i].altdown);
      if (t1<=ft)
      {
        printRoute(A[i],roundup(t1));
        if (t2<=ft && strcmp(A[i].startpoint, A[i].endpoint)!=0)
        {
          printRouteReturn(A[i],roundup(t2));
        }
      }
      else
      {
        if (t2<=ft)
          printRouteReturn(A[i],roundup(t2));
      }
    }
}

struct route *readFromFile(int *n)
{
  int i,m;
  char *fn;
  struct route *A;
  FILE *fp;
  fn = (char *)malloc(30*sizeof(char));
  fgets(fn, 30, stdin);
  fn[strcspn(fn, "\n")]='\0';
  fn = (char *)realloc(fn, (strlen(fn)+1)*sizeof(char));
  fp = fopen(fn,"r");
  if (fp!=NULL)
  {
    fscanf(fp, "%d", &m);
    A = (struct route *)malloc(m*sizeof(struct route));
    for (i=0;i<m;i++)
      {
        fscanf(fp, " ");
        fgets(A[i].startpoint, 50, fp);
        A[i].startpoint[strcspn(A[i].startpoint, "\n")]='\0';
        fscanf(fp, "%d %d %d %d %d", &A[i].length, &A[i].altup, &A[i].altdown, &A[i].altmax, &A[i].altmin);
        fscanf(fp, " ");
        fgets(A[i].endpoint, 50, fp);
        A[i].endpoint[strcspn(A[i].endpoint, "\n")]='\0';
      }
  }
  *n=m;
  fclose(fp);
  return A;
}

void saveData(struct route *A, int n)
{
  int i,j,t;
  struct route temp;
  FILE *fp;
  char *fn;
  //A=(struct route *)malloc(n*sizeof(struct route));
  for (i=1;i<n;i++)
    {
      for (j=n;j>=i;j--)
        {
          if (A[j-1].length<A[j].length)
          {
            temp=A[j-1];
            A[j-1]=A[j];
            A[j]=temp;
          }
        }
    }


  fn = (char *)malloc(30*sizeof(char));
  
  fgets(fn, 30, stdin);
  fn[strcspn(fn, "\n")]='\0';

  fn = (char *)realloc(fn, (strlen(fn)+1)*sizeof(char));
  
  fp = fopen(fn ,"a");

  if (fp!=NULL)
  {
    for (i=0;i<n;i++)
      {
        t = estimatedTime(A[i].length, A[i].altup);
        fputs("From ", fp);
        fputs(A[i].startpoint, fp);
        fputs(" to ", fp);
        fputs(A[i].endpoint, fp);
        fputc('\n', fp);
        fputs("Uphill ", fp);
        fprintf(fp, "%d", A[i].altup);
        fputs(", Downhill ", fp);
        fprintf(fp, "%d\n", A[i].altdown);
        fputs("Max altitude ", fp);
        fprintf(fp, "%d", A[i].altmax);
        fputs(", Min altitude ", fp);
        fprintf(fp, "%d\n", A[i].altmin);
        fputs("Length ", fp);
        fprintf(fp, "%d", A[i].length);
        fputs(", Estimated time ", fp);
        fprintf(fp, "%d", t);
        fputs(" min", fp);
        fputs("\n", fp);
        fputs("\n", fp);

        if (strcmp(A[i].startpoint, A[i].endpoint)!=0)
        {
          t = estimatedTime(A[i].length, A[i].altdown);
          fputs("From ", fp);
          fputs(A[i].endpoint, fp);
          fputs(" to ", fp);
          fputs(A[i].startpoint, fp);
          fputc('\n', fp);
          fputs("Uphill ", fp);
          fprintf(fp, "%d", A[i].altdown);
          fputs(", Downhill ", fp);
          fprintf(fp, "%d\n", A[i].altup);
          fputs("Max altitude ", fp);
          fprintf(fp, "%d", A[i].altmax);
          fputs(", Min altitude ", fp);
          fprintf(fp, "%d\n", A[i].altmin);
          fputs("Length ", fp);
          fprintf(fp, "%d", A[i].length);
          fputs(", Estimated time ", fp);
          fprintf(fp, "%d", t);
          fputs(" min", fp);
          fputs("\n", fp);
          fputs("\n", fp);
        }
      }
  }
  fclose(fp);
}