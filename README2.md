#SimulaciónFísica
PRÁCTICA 5: SÓLIDO RÍGIDO

---nuevas implementaciones/cambios generales:
CLASE OBJECT/RIGIDBODY:
En esta práctica he creado una clase padre Object de Particle con todos los métodos que se usan en generadores de partículas o fuerzas virtuales. Así Particle y el nuevo hijo de Object, RigidBody, podrán incorporarse a un mismo sistema con unas fuerzas compartidas. Para que no se duplique la fuerza de la gravedad sobre los sólidos rigidos, en el main la he setteado a 0. Así el usuario puede seguir activándola y desactivándola como anteriormente. 

RigidBody tiene los métodos de particle actualizados con cómo se obtienen/modifican los datos de un sólido rígido. 

Todos los archivos que incluyen la palabra particle en el ahora funcionan para cualquier objeto de clase Object.  ParticleSystem realmente sería ahora ObjectSystem. 

GENERATORS:
He cambiado el ParticleGenerator para que si se le pasa un máximo de partículas no se generen más que las indicadas (_maxTotalParticles) para que no se generen demasiados objetos de tipo SolidRigid.

---escena/activar fuerzas:
Todas las fuerzas como generadores funcionan sobre tanto RigidBody como Particle. Presionando la i en ejecución el usuario verá en consola que comandos usar para activar las diferentes fuerzas. Fireworks sigue generando únicamente partículas. Se puede comprobar que funcionan correctamente las partículas descomentando las escenas de los muelles o los generadores de partículas.



