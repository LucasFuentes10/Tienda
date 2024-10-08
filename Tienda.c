#include <stdio.h>
#include <string.h> // Para usar funciones de manejo de cadenas

#define MAX_PRODUCTOS 5  // Definir constante para el número máximo de productos

// Enumeración para las categorías
typedef enum {
    ALIMENTOS,
    ROPA,
    ELECTRONICA
} Categoria;

// Estructura para representar un producto
typedef struct {
    char nombre[50];
    Categoria categoria;
    float precio;
    union {
        char fecha_caducidad[11];  // Para Alimentos (dd/mm/yyyy)
        char talla[5];              // Para Ropa (S, M, L, etc.)
        int garantia_meses;         // Para Electrónica (en meses)
    } detalle;
} Producto;

// Declaración de los subprogramas
void agregarProducto(Producto productos[], int *num_productos);
void mostrarProductos(Producto productos[], int num_productos);
float calcularValorTotal(Producto productos[], int num_productos);
void mostrarPorCategoria(Producto productos[], int num_productos);

int main() {
    Producto productos[MAX_PRODUCTOS];
    int num_productos = 0;
    int opcion;

    do {
        printf("\n--- MENU TIENDA ---\n");
        printf("1. Agregar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Calcular valor total del inventario\n");
        printf("4. Mostrar productos por categoría\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto(productos, &num_productos);
                break;
            case 2:
                mostrarProductos(productos, num_productos);
                break;
            case 3:
                printf("El valor total del inventario es: $%.2f\n", calcularValorTotal(productos, num_productos));
                break;
            case 4:
                mostrarPorCategoria(productos, num_productos);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    return 0;
}

// Subprograma para agregar un nuevo producto
void agregarProducto(Producto productos[], int *num_productos) {
    if (*num_productos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos, inventario lleno.\n");
        return;
    }

    Producto nuevo_producto;
    int categoria;

    printf("Ingrese el nombre del producto: ");
    getchar();  // Limpiar buffer
    fgets(nuevo_producto.nombre, 50, stdin);
    nuevo_producto.nombre[strcspn(nuevo_producto.nombre, "\n")] = 0; // Eliminar salto de línea

    printf("Seleccione la categoría (0: Alimentos, 1: Ropa, 2: Electrónica): ");
    scanf("%d", &categoria);
    nuevo_producto.categoria = (Categoria)categoria;

    printf("Ingrese el precio del producto: ");
    scanf("%f", &nuevo_producto.precio);

    switch (nuevo_producto.categoria) {
        case ALIMENTOS:
            printf("Ingrese la fecha de caducidad (dd/mm/yyyy): ");
            scanf("%s", nuevo_producto.detalle.fecha_caducidad);
            break;
        case ROPA:
            printf("Ingrese la talla (S, M, L, XL, etc.): ");
            scanf("%s", nuevo_producto.detalle.talla);
            break;
        case ELECTRONICA:
            printf("Ingrese la garantía en meses: ");
            scanf("%d", &nuevo_producto.detalle.garantia_meses);
            break;
        default:
            printf("Categoría no válida.\n");
            return;
    }

    productos[*num_productos] = nuevo_producto;
    (*num_productos)++;
    printf("Producto agregado con éxito.\n");
}

// Subprograma para mostrar todos los productos disponibles
void mostrarProductos(Producto productos[], int num_productos) {
    if (num_productos == 0) {
        printf("No hay productos en la tienda.\n");
        return;
    }

    for (int i = 0; i < num_productos; i++) {
        printf("\nProducto %d\n", i + 1);
        printf("Nombre: %s\n", productos[i].nombre);
        printf("Precio: $%.2f\n", productos[i].precio);

        switch (productos[i].categoria) {
            case ALIMENTOS:
                printf("Categoría: Alimentos\n");
                printf("Fecha de caducidad: %s\n", productos[i].detalle.fecha_caducidad);
                break;
            case ROPA:
                printf("Categoría: Ropa\n");
                printf("Talla: %s\n", productos[i].detalle.talla);
                break;
            case ELECTRONICA:
                printf("Categoría: Electrónica\n");
                printf("Garantía: %d meses\n", productos[i].detalle.garantia_meses);
                break;
        }
    }
}

// Subprograma para calcular el valor total del inventario
float calcularValorTotal(Producto productos[], int num_productos) {
    float valor_total = 0.0;
    for (int i = 0; i < num_productos; i++) {
        valor_total += productos[i].precio;
    }
    return valor_total;
}

// Subprograma para mostrar productos por categoría
void mostrarPorCategoria(Producto productos[], int num_productos) {
    if (num_productos == 0) {
        printf("No hay productos en la tienda.\n");
        return;
    }

    int categoria;
    printf("Seleccione la categoría a mostrar (0: Alimentos, 1: Ropa, 2: Electrónica): ");
    scanf("%d", &categoria);

    // Validar que la categoría ingresada esté dentro del rango válido
    if (categoria < 0 || categoria > 2) {
        printf("Categoría no válida. Por favor, seleccione un número entre 0 y 2.\n");
        return;
    }

    int encontrado = 0; // Variable para verificar si se encontró al menos un producto
    for (int i = 0; i < num_productos; i++) {
        if (productos[i].categoria == categoria) {
            if (!encontrado) {
                printf("\n--- Productos en la categoría seleccionada ---\n");
                encontrado = 1; // Marca que se encontró al menos un producto
            }
            printf("\nProducto %d\n", i + 1);
            printf("Nombre: %s\n", productos[i].nombre);
            printf("Precio: $%.2f\n", productos[i].precio);
            switch (productos[i].categoria) {
                case ALIMENTOS:
                    printf("Fecha de caducidad: %s\n", productos[i].detalle.fecha_caducidad);
                    break;
                case ROPA:
                    printf("Talla: %s\n", productos[i].detalle.talla);
                    break;
                case ELECTRONICA:
                    printf("Garantía: %d meses\n", productos[i].detalle.garantia_meses);
                    break;
            }
        }
    }

    if (!encontrado) {
        printf("No se encontraron productos en la categoría seleccionada.\n");
    }
}