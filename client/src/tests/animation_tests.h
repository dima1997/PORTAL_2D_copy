#ifndef ANIMATION_TESTS_H
#define ANIMATION_TESTS_H

/*
Muetra la textura de un bloque, 
con coordenada superior izquierda, 
en el centro de la ventana.
*/
void testShowOneBlock();

/*
Muetra las texturas de 3 bloques,
con coordenadas superiores izquierda,
en el centro de la ventana, uno al lado 
del otro (sin solaparse).
*/
void testShowThreeBlocks();

/*
Muetra todo el borde inferior de la 
ventana cubierto de texturas de bloque.
(Los bloques no deben solaparse)
*/
void testShowGroundOfBlocks();

/*
Muetra todo el marco de la ventana 
cubierta de texturas de bloques.
(Los bloques no deben solaparse)
Los bloques en el borde inferior 
pueden quedar cortados, y eso esta 
bien.
*/
void testShowFrameOfBlocks();
/*
Muetra una textura de bloque, 
con coordenada superior izquierda,
anterior al 0,0, correspondiente a
la esquina superior izquierda de la 
ventana.
Solo se debe ver la seccion del bloque 
que cuyas coordenadas son superior al 
origen de la ventana.
*/
void testShowPartOfBlockFarBeferoOrigin();

/*
Muetra un chell en el centro de la ventana.
*/
void testShowChell();

/*
Muestra una chell sudando
*/
void testAnimateChellSweat();

/*
Muestra a Chell desplazandose de hacia derecha y deteniendose.
*/
void testAnimateChellRunning();

/*
Muestra a Chell saltando verticalmente y hacia la derecha.
*/
void testAnimateChellJumping();

/*
Ejecuta la animacion de chell sudando, renderizandola desde el 
AnimationLoopThread; y controlando la entrada del usuario a traves
del KeyReaderThread. 
(En este caso , la entrada del usuario es solo cerrar la ventana)
*/
//void testAnimationLoopKeyReader();

#endif // ANIMATION_TESTS_H