#include <stdio.h>

#define MAX_PRODUCTOS 5  


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
        char talla[5];             // Para Ropa (S, M, L, etc.)
        int garantia_meses;        // Para Electrónica (en meses)
    } detalle;
} Producto;


void agregarProducto(Producto productos[], int *num_productos);
void mostrarProductos(Producto productos[], int num_productos);
float calcularValorTotal(Producto productos[], int num_productos);

int main() {
    Producto productos[MAX_PRODUCTOS];
    int num_productos = 0;
    int opcion;

    do {
        printf("\n--- MENU TIENDA ---\n");
        printf("1. Agregar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Calcular valor total del inventario\n");
        printf("4. Salir\n");
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
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

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
