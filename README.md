<h1>Gestionamiento de citas en una estética veterinaria</h1>
<p>El objetivo principal de este proyecto es saber implementar métodos de busqueda y ordenamiento en C++; de igual forma el manejo de las estructuras <b>struct</b> para gestionar datos de una manera más propia.<p>

## funciones que debe implementar la aplicación:

- ### Registro de citas
<p>Permite al administrador agregar citas para su mascota agregando los servicios con los que contamos (baño, corte de pelo, corte de uñas, limpieza de oidos, lavado de dientes).<p>

- ### Consultar cita
<p>Deja al administrador visualizar las citas que hay generadas,además que exista una opción para poder hacer una busqueda por id, nombre del dueño o de la mascota así como también su ordenamiento de maneras descendente y ascendente.</p>

- ### Modificar cita
<p>El administrador de las citas en la <b>estetica canina</b> debe de contar con la opción de modificar la fecha, hora de entrada por si el dueño de la mascota deseara cambiar la cita; para realizar este cambio se puede realizar proporcionando el nombre del dueño, id de la cita o nombre de la mascota<p>

- ### Cancelar/borrar una cita
<p>En dado caso de que el cliente por algún motivo desee cancelar la cita se podrá realizar proporcionando un ID o el nombre del dueño y/o mascota<p>

- ### Añadir un nuevo cliente
<p>Nos permite agregar un nuevo cliente si es que es la primera vez que solicita nuestro servicio añadiendo datos (nombres, apellido paterno, materno, telefono, correo, domicilio) <p>

## Puntos a tomar en cuenta:

- El numero de clientes es máximo de 20.
- La cantidad de mascotas máxima que puede tener el cliente es de 5.
- Se requiere validaciones y/o manejo de sentencia de errores dependiendo el tipo de variable.
- Manejar la libreria <time.h> para la lectura de los horarios, ya que al generar la cita se requiere mostrar la fecha de entrada, hora (estimada) de la mascota.
- El horario a tomar en cuenta de 9:00 a 17:00, se trabaja todos los días.
- No se tiene permitido usar vectores y librerias que permitan realizar los métodos de busqueda y ordenamiento generadas por compilador.
- Los métodos de busqueda y ordenamiento se tienen que realizar con funciones.
- Se requiere que los métodos sean los más eficientes


