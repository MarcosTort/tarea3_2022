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
    lineaux(cad, izquierdo(b)); // llegar al menor
    TInfo dato = raiz(b);
    cad = insertarAlFinal(natInfo(dato), realInfo(dato), cad); // insertar de mayor a menor de izq
    lineaux(cad, derecho(b));
    return cad;
  }
  else
    return NULL;
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
    return NULL;
  }
  else if (esVacioAbb(izquierdo(abb)) || esVacioAbb(derecho(abb)))
  {
    return false;
  }
  else if (esVacioAbb(izquierdo(abb)) && esVacioAbb(derecho(abb)))
  {
    return (profundidad == nivel + 1);
  }
  else
  {
    return esPerfectoAUX(izquierdo(abb), profundidad, nivel + 1) && esPerfectoAUX(izquierdo(abb), profundidad, nivel + 1);
  }
}
int profAbb(TAbb abb)
{
  int d = 0;
  while (abb != NULL)
  {
    d++;
    abb = izquierdo(abb);
  }
  return d;
}
bool esPerfecto(TAbb abb)
{
  int profundidad = profAbb(abb);
  int nivelInicial = 0;
  return esPerfectoAUX(abb, profundidad, nivelInicial);
}

TAbb menores(double limite, TAbb abb)
{
  // TAbb res;
  // if (limite > 0 && abb != NULL)
  // {
  //   TAbb bizq, bder;
  //   bizq = menores(limite, izquierdo(abb));
  //   bder = menores(limite, derecho(abb));
  //   if (realInfo(raiz(abb)) < limite)
  //   {
  //     res = crearAbb();
  //     res = insertarEnAbb(copiaInfo(raiz(abb)), res);
  //     TAbb izq = izquierdo(res);
  //     TAbb der = derecho(res);
  //     // izq = bizq;
  //     // der = bder;
  //   }
  //   else
  //   {
  //     if (bizq == NULL)
  //       res = bder;
  //     else if (bder == NULL)
  //       res = bizq;
  //     else
  //     {
  //       res = crearAbb();
  //       res = insertarEnAbb(copiaInfo(raiz(abb)), res);
  //       TAbb izq = izquierdo(res);
  //       TAbb der = derecho(res);
  //       izq = bizq;
  //       der = bder;
  //       removerDeAbb(natInfo(raiz(abb)), res);
  //     }
  //   }
  // }
  // else
  //   res = NULL;
  return NULL;
}

TIterador caminoAscendente(nat clave, nat k, TAbb abb)
{
  TAbb aux = abb;
  TIterador iter = crearIterador();
  while (aux != NULL)
  {
    if (natInfo(raiz(aux)) == clave)
    {
      if (k == 0)
      {
        agregarAIterador(natInfo(raiz(aux)), iter);
        return iter;
      }
      else
      {
        k--;
        aux = izquierdo(aux);
      }
    }
    else if (natInfo(raiz(aux)) > clave)
    {
      if (k == 0)
      {
        agregarAIterador(natInfo(raiz(aux)), iter);
        return iter;
      }
      else
      {
        k--;
        aux = izquierdo(aux);
      }
    }
    else
    {
      if (k == 0)
      {
        agregarAIterador(natInfo(raiz(aux)), iter);
        return iter;
      }
      else
      {
        k--;
        aux = derecho(aux);
      }
    }
  }
  return iter;
}

void imprimirPalabrasCortas(nat k, TPalabras palabras)
{

  if (palabras != NULL)
  {

    if (k > 0)
    {
      printf("%c", letra(palabras));
    }
    else
    {
      printf("\n");
    }
    imprimirPalabrasCortas(k - 1, subarboles(palabras));
    imprimirPalabrasCortas(k - 1, siguientes(palabras));
  }
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras)
{
  return NULL;
}

// auxiliares
