/* 5286580 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/cadena.h"
#include "../include/iterador.h"
#include <string.h>
TCadena insertarAlFinal(nat natural, double real, TCadena cad)
{
  cad = insertarAlInicio(natural, real, cad);
  cad = cadenaSiguiente(cad);
  return cad;
}

TCadena removerPrimero(TCadena cad)
{
  cad = removerDeCadena(natInfo(primeroEnCadena(cad)), cad);
  return cad;
}

TCadena copiaCadena(TCadena cad)
{
  if (cad != NULL)
  {
    TCadena copia = crearCadena();
    TCadena partida = cad;
    TCadena siguiente = cad;
    TInfo info = primeroEnCadena(cad);
    copia = insertarAlFinal(natInfo(info), realInfo(info), copia);
    siguiente = cadenaSiguiente(siguiente);

    while (siguiente != partida)
    {
      TInfo info = primeroEnCadena(siguiente);
      copia = insertarAlFinal(natInfo(info), realInfo(info), copia);
      siguiente = cadenaSiguiente(siguiente);
    }
    return copia;
  }
  else
    return NULL;
}

TIterador reversoDeIterador(TIterador iter)
{
  TIterador reverso = crearIterador();

  reiniciarIterador(iter);
  reiniciarIterador(reverso);
  TCadena aux = crearCadena();
  int count = 0;
  while (estaDefinidaActual(iter))
  {
    nat entrante = actualEnIterador(iter);
    aux = insertarAlInicio(entrante, 0, aux);
    avanzarIterador(iter);
    count++;
  }

  for (int i = 0; i < count; i++)
  {
    agregarAIterador(natInfo(primeroEnCadena(aux)), reverso);
    aux = cadenaSiguiente(aux);
  }
  liberarCadena(aux);
  reiniciarIterador(reverso);

  return reverso;
}

TCadena lineaux(TCadena cad, TAbb b)
{ // LISTO
  if (!esVacioAbb(b))
  {

    cad = lineaux(cad, izquierdo(b)); // llegar al menor
    TInfo dato = raiz(b);
    cad = insertarAlFinal(natInfo(dato), realInfo(dato), cad); // insertar de mayor a menor de izq
    cad = lineaux(cad, derecho(b));
    return cad;
  }
  else
    return cad;
}

TCadena linealizacion(TAbb abb)
{

  TCadena cad = crearCadena();
  cad = lineaux(cad, abb);
  return cad;
}
void aux2(nat nivel, TAbb b)
{

  for (nat i = 0; i < nivel; i++)
    printf("-");
  char *infotxt = infoATexto(raiz(b));
  printf("%s", infotxt);
  delete[] infotxt;
}
void imprimiraux(nat nivel, TAbb b)
{
  if (!esVacioAbb(b))
  {
    imprimiraux(nivel + 1, derecho(b));
    aux2(nivel, b);
    printf("\n");
    imprimiraux(nivel + 1, izquierdo(b));
  }
}
void imprimirAbb(TAbb abb)
{
  if (esVacioAbb(abb))
  {
    return;
  }
  imprimiraux(0, abb);
}

bool esPerfectoAUX(TAbb abb, nat profundidad, nat nivel)
{

  if (esVacioAbb(abb))
  {
    // printf("%d", __LINE__);

    return true;
  }
  else if (esVacioAbb(izquierdo(abb)) && esVacioAbb(derecho(abb)))
  {
    // printf("%d", __LINE__);
    return (profundidad == nivel);
  }
  else if (esVacioAbb(izquierdo(abb)) || esVacioAbb(derecho(abb)))
  {
    // printf("%d", __LINE__);
    return false;
  }

  else
  {
    // printf("%d", __LINE__);
    return esPerfectoAUX(izquierdo(abb), profundidad, nivel + 1) && esPerfectoAUX(derecho(abb), profundidad, nivel + 1);
  }
}
int maxDepth(TAbb node)
{
  if (node == NULL)
    return -1;
  else
  {
    /* compute the depth of each subtree */
    int lDepth = maxDepth(izquierdo(node));
    int rDepth = maxDepth(derecho(node));

    /* use the larger one */
    if (lDepth > rDepth)
      return (lDepth + 1);
    else
      return (rDepth + 1);
  }
}
bool esPerfecto(TAbb abb)
{
  int profundidad = maxDepth(abb);
  int nivelInicial = 0;
  return esPerfectoAUX(abb, profundidad, nivelInicial);
}

TAbb menores(double cota, TAbb b)
{
  TAbb res;
  if (cota > 0 && b != NULL)
  {
    TAbb bizq, bder;
    bizq = menores(cota, izquierdo(b));
    bder = menores(cota, derecho(b));
    if (realInfo(raiz(b)) < cota)
    {
      res = consAbb(copiaInfo(raiz(b)), bizq, bder);
    }
    else
    {
      if (bizq == NULL)
        res = bder;
      else if (bder == NULL)
        res = bizq;
      else
      {
        res = consAbb(copiaInfo(raiz(b)), bizq, bder);
        removerDeAbb(natInfo(raiz(res)), res);
      }
    }
  }
  else
    res = NULL;
  return res;
}

int minimo(int a, int b)
{
  if (a < b)
    return a;
  else
    return b;
}
TIterador caminoAscendente(nat clave, nat k, TAbb abb)
{
  int count = 1;
  TIterador iter = crearIterador();
  TAbb aux = abb;
  while (clave != natInfo(raiz(aux)))
  {
    if (!esVacioAbb(aux))
    {
      agregarAIterador(natInfo(raiz(aux)), iter);
      count++;
      // SI EL BUSCADO ES MAS GRANDE QUE LA RAIZ ACTUAL
      if (clave > natInfo(raiz(aux)))
      {
        aux = derecho(aux);
      }
      else if (clave < natInfo(raiz(aux)))

      {
        aux = izquierdo(aux);
      }
    }
  }
  agregarAIterador(natInfo(raiz(aux)), iter);

  TIterador res = reversoDeIterador(iter);
  reiniciarIterador(res);
  liberarIterador(iter);
  TIterador auxIter = crearIterador();

  for (int i = 0; i < minimo(count, k); i++)
  {
    nat auxNat = actualEnIterador(res);
    agregarAIterador(auxNat, auxIter);
    avanzarIterador(res);
  }
  liberarIterador(res);
  return auxIter;
}
ArregloChars reverse(ArregloChars array, nat size)
{
  for (nat i = 0; i < size / 2; i++)
  {
    nat aux = array[i];
    array[i] = array[size - i - 1];
    array[size - i - 1] = aux;
  }
  return array;
}
void imprimirPalabrasCortasAux(int i, int k, TPalabras palabras, ArregloChars salida)
{

  if (palabras != NULL)
  {
    // printf("nashe    %c\n", letra(palabras));
    // printf("%d\n", k);
    salida[i - k] = letra(palabras);

    if (k >= 0 && letra(palabras) == '\0')
    {
      // printf("%d\n", k);
      printf("%s\n", salida);
    }

    imprimirPalabrasCortasAux(i, k - 1, subarboles(palabras), salida);
    if (k != i)
      imprimirPalabrasCortasAux(i, k, siguientes(palabras), salida);
  }
}

void imprimirPalabrasCortas(nat k, TPalabras palabras)
{
  ArregloChars salida = new char[1000];
  palabras = subarboles(palabras);
  while (palabras != NULL)
  {

    imprimirPalabrasCortasAux(k, k, palabras, salida);
    palabras = siguientes(palabras);
  }
  delete[] salida;
}

// int largoArray(ArregloChars array)
// {
//   int i = 0;
//   while (array[i] != NULL)
//   {
//     i++;
//   }
//   return i;
// }

TPalabras buscarFinPrefijoAux(ArregloChars prefijo, TPalabras palabras, int nivel)
{
  if (palabras != NULL)
  {
    palabras = subarboles(palabras);
    while (palabras != NULL && prefijo[nivel] != letra(palabras))
    {
      palabras = siguientes(palabras);
    }
    if (palabras != NULL && prefijo[nivel + 1] != '\0')

    {
      palabras = buscarFinPrefijoAux(prefijo, palabras, nivel + 1);
    }
    return palabras;
  }
  else
    return NULL;
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras)
{
  return buscarFinPrefijoAux(prefijo, palabras, 0);
}

// auxiliares

void aux2(nat nivel, TPalabras b)
{
  for (nat i = 0; i < nivel; i++)
    printf("-");
  char infotxt = letra(b);
  printf("%c", infotxt);
}
void imprimiraux(nat nivel, TPalabras b)
{
  if (b != NULL)
  {
    imprimiraux(nivel + 1, subarboles(b));
    aux2(nivel, b);
    printf("\n");
    imprimiraux(nivel + 1, siguientes(b));
  }
}

void pal(TPalabras abb)
{
  if (abb == NULL)
  {
    return;
  }
  imprimiraux(0, abb);
}
