# edi3-pf-2018
Proyecto final EDI 3 2018

<h1>Listado de tareas/ramas de trabajo y responsable/s</h1>
<ol>
    <li>First Commit Compset - Restructuración y Diseño:</li>
    <ul><li>Gabriel</li></ul>
    <li>Modulos de conexión y uso de motores de base de datos:
        <ul>
            <li>MariaDB(MySQL):  Nano</li>
            <li>SQLITE: Diego y Sebastián.</li>
            <li>PostgreSQL: Leonardo y Jona</li>
        </ul>
    </li>
    <li>Integrar biblioteca de tercero https://github.com/nlohmann/json con la interface de "DocumentGenerator". unordered_map<string, string> o directamente pasar de la consulta a la base de datos al tipo json:
        <ul>
            <li>Francisco y Florencia -> Escribir pruebas de uso de json</li>
        </ul>
    </li>
    <li>Base Datos: implementar las tablas necesarias para Authentication y Authorization. Escribir los procedimientos de alta, baja y modificación de las tablas users, roles, actions:
        <ul>
            <li>Facundo</li>
        </ul>
    </li>
    <li>QA: Pruebas contras las interfaces, no es necesario frameworks, pero pueden usar assert, etc:
        <ul>
            <li>Giuliano -> XmlDocumentGenerator</li>
            <li>Lucas -> RequestHandler (formato estándar URI)</li>
            <li>Hernán -> PostgreDatabaseHandler</li>
            <li>Dai -> ComponentFactory</li>
            <li>Celeste -> JsonDocumentGenerator</li>
            <li>Paula -> ResponseHandler</li>
        </ul>
    </li>
    <li>Boris (una actividad especial)-> completar LibraryLoader para dar soporte a Apple OSx y crear útil/helper -> lector de archivos .ini: IniReader.h</li>
</ol>
