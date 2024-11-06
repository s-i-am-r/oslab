#include <gtk/gtk.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

#define THINKING 0 
#define HUNGRY 1
#define EATING 2

int PHILS[5];
bool FORKS[5];
pthread_t THREADS[5];
GtkWidget *philosophers[5]; // Widgets representing philosophers
GtkWidget *labels[5]; // Labels for philosopher IDs

// Function to update philosopher color based on state
gboolean update_philosopher_color(gpointer data) {
    int me = GPOINTER_TO_INT(data);
    GdkRGBA color;

    if (PHILS[me] == THINKING) {
        gdk_rgba_parse(&color, "white");
    } else if (PHILS[me] == HUNGRY) {
        gdk_rgba_parse(&color, "yellow");
    } else if (PHILS[me] == EATING) {
        gdk_rgba_parse(&color, "green");
    }

    gtk_widget_override_background_color(philosophers[me], GTK_STATE_FLAG_NORMAL, &color);
    return FALSE;
}

void signal_handler(int signum) {
    printf("Thread received signal %d and woke up!\n", signum);
}

void a_phil(int me, bool* forks, int* phils, pthread_t* threads) {
    think:
    phils[me] = THINKING;
    g_idle_add(update_philosopher_color, GINT_TO_POINTER(me)); // Update color in GUI
    usleep(5000000 + rand() % 5000000);

    try_eat:
    if (forks[me] && forks[(me + 1) % 5]) {
        forks[me] = forks[(me + 1) % 5] = false;
        phils[me] = EATING;
        g_idle_add(update_philosopher_color, GINT_TO_POINTER(me)); // Update color in GUI
        usleep(5000000 + rand() % 5000000);
        forks[me] = forks[(me + 1) % 5] = true;

        if (phils[(me + 4) % 5] == HUNGRY && forks[(me + 4) % 5]) {
            pthread_kill(threads[(me + 4) % 5], SIGUSR1);
        } else if (phils[(me + 1) % 5] == HUNGRY && forks[(me + 2) % 5]) {
            pthread_kill(threads[(me + 1) % 5], SIGUSR1);
        }
        goto think;
    } else {
        phils[me] = HUNGRY;
        g_idle_add(update_philosopher_color, GINT_TO_POINTER(me)); // Update color in GUI
        pause();
        goto try_eat;
    }
}

void* thread_func(void* n) {
    int me = *(int*)n;
    signal(SIGUSR1, signal_handler);
    a_phil(me, FORKS, PHILS, THREADS);
    return NULL;
}

// Function to position the philosophers in a pentagon shape
void setup_gui(GtkWidget* window) {
    GtkWidget* fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    int radius = 200; // Radius of the pentagon
    int center_x = 300; // X center of the pentagon
    int center_y = 300; // Y center of the pentagon

    // Position philosophers in a pentagon shape
    for (int i = 0; i < 5; i++) {
        philosophers[i] = gtk_button_new(); // Create button for each philosopher
        gtk_widget_set_size_request(philosophers[i], 100, 100);

        // Position each philosopher at pentagon vertices
        int x = center_x + radius * cos(2 * M_PI * i / 5 - M_PI / 2);
        int y = center_y + radius * sin(2 * M_PI * i / 5 - M_PI / 2);
        gtk_fixed_put(GTK_FIXED(fixed), philosophers[i], x, y);

        // Add label for philosopher ID inside the button
        char label_text[10];
        snprintf(label_text, sizeof(label_text), "Phil %d", i);
        labels[i] = gtk_label_new(label_text);
        gtk_container_add(GTK_CONTAINER(philosophers[i]), labels[i]);
    }

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Initialize forks
    for (size_t i = 0; i < 5; i++) {
        FORKS[i] = true;
    }

    // Create GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Dining Philosophers");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Setup GUI layout
    setup_gui(window);

    // Start philosopher threads
    int tmp[] = {0, 1, 2, 3, 4};
    for (size_t i = 0; i < 5; i++) {
        pthread_create(&THREADS[i], NULL, thread_func, &tmp[i]);
    }

    gtk_main();

    // Wait for philosopher threads to finish
    for (size_t i = 0; i < 5; i++) {
        pthread_join(THREADS[i], NULL);
    }

    return 0;
}
