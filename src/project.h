#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#define OPTIONS_FILE "dta1d.options"

#include <gtk/gtk.h>
#include <locale.h>

#include "../config.h"

typedef struct
{
 gdouble dose_difference; //in %
 gdouble dta; // in mm
 GdkRGBA color_1;
 GdkRGBA color_2;
} options;

options global_options;


typedef struct
{
  guint first_row;
  guint last_row;
}omnipro_dataset;

typedef struct
{
  gdouble x;
  gdouble dose;
  gdouble result; //filled after comparing two arrays
  gchar* desc; //filled while evaluating an algorithm, for debugging or showing how it works
} point;

guint monaco_graph_type;
guint csv_graph_type; // crossline--1 inline--2; undefined--0; depth--3;
//graph type
#define  GT_UNDEFINED 0
#define  GT_CROSSLINE 1
#define  GT_INLINE 2
#define  GT_DEPTH 3

//normalization type
#define NORM_TO_MAX 0
#define NORM_TO_CENTER 1

//algorithms
#define SIMPLE_DTA 0
#define COMPLEX_DTA 1
#define GAMMA 2

gint algorithm = SIMPLE_DTA;//for now - this should be able to choose in options window

//GtkWidget *data_0;
//GtkWidget *data_1;

GtkWidget *main_window;
GtkWidget *main_box; //menu + main_hbox
GtkWidget *main_hbox;

//menu
GtkWidget *main_menu_bar;
GtkWidget *menu_item_file;
GtkWidget *menu_item_monaco;
GtkWidget *menu_item_omnipro;

GtkWidget *menu_file;
GtkWidget *menu_item_options;
GtkWidget *menu_item_report;
GtkWidget *menu_item_about;
GtkWidget *menu_item_exit;

GtkWidget *menu_monaco;
GtkWidget *menu_item_open_monaco_plane;
GtkWidget *menu_item_save_monaco_row;
GtkWidget *menu_item_save_monaco_column;

GtkWidget *menu_omnipro;
GtkWidget *menu_item_open_omnipro_csv;
//end of menu

GtkWidget *hhbox;

GtkWidget *monaco_da;

GtkWidget *monaco_frame;
GtkWidget *monaco_hbox;
//GtkWidget *monaco_vbox;
GtkWidget *monaco_vbox_menu;
GtkWidget *monaco_vbox_2;
//GtkWidget *monaco_diag_frame;

GtkWidget *monaco_la_1;
GtkWidget *monaco_ed1_hbox;
GtkWidget *monaco_ed_1;
GtkWidget *monaco_bu_1;
GtkWidget *monaco_la_2;
GtkWidget *monaco_ed2_hbox;
GtkWidget *monaco_ed_2;
GtkWidget *monaco_bu_2;
GtkWidget *monaco_la_3;
GtkWidget *monaco_la_4;
GtkWidget *monaco_la_5;
GtkWidget *monaco_rb_1;
GtkWidget *monaco_rb_2;
GtkWidget *monaco_rb_3;


GtkWidget *monaco_scrolled_window;
GtkTextBuffer *monaco_text_buffer;
GtkWidget *monaco_text_view;

GtkWidget *omnipro_frame;
GtkWidget *omnipro_hbox;
//GtkWidget *omnipro_vbox;
GtkWidget *omnipro_vbox_menu;
//GtkWidget *omnipro_diag_frame;


GtkWidget *omnipro_la_1;
GtkWidget *omnipro_combo_box_text;
GtkWidget *omnipro_button;
GtkWidget *omnipro_la_2;
GtkWidget *omnipro_la_3;
GtkWidget *omnipro_la_4;

GtkWidget *omnipro_scrolled_window;
GtkTextBuffer *omnipro_text_buffer;
GtkWidget *omnipro_text_view;
GtkWidget *omnipro_da;

GtkWidget *compare_vbox; //compare_hbox + compare_da
GtkWidget *compare_hbox; //compare_button + compare_rb_1 + compare_rb_2
GtkWidget *compare_button;
GtkWidget *compare_rb_1;//1vs2
GtkWidget *compare_rb_2;//2vs1

GtkWidget *compare_da;
GtkWidget *msg_bar;
GtkWidget *msg_label;

guint64 n_of_x, n_of_y;
guint64 monaco_row_val, monaco_column_val;
gdouble monaco_step = 0;
gdouble omnipro_step = 0;

gchar **lines_splitted = NULL;
gchar **csv_splitted = NULL;

guint n_of_lines;
guint n_of_csv_lines;
guint n_of_csv_sets;

// Arrays with point structures (most of them)
GArray *monaco_garray = NULL; 
GArray *omnipro_points_garray = NULL; // with points
GArray *omnipro_sets_garray = NULL; // with omnipro_datasets
GArray *checked_garray_trimmed = NULL; // this it the array we want to compare, filled with points
GArray *the_other_garray = NULL; // this is the array we want to compare to, filled with points

// FUNCTIONS //

/* Monaco manipulating functions defined in monaco_functions.c */
void open_monaco_plane_clicked(  );
void save_monaco_row_clicked(  );
void get_monaco_row_clicked(  );
void save_monaco_column_clicked(  );
void get_monaco_column_clicked(  );

void draw_background( cairo_t *_cr, guint _width, guint _height, guint _x, guint _y );

static void begin_print( GtkPrintOperation *operation, GtkPrintContext *context, gpointer user_data );
static void draw_page( GtkPrintOperation *operation, GtkPrintContext *context, gint page_nr, gpointer user_data );
static void end_print (GtkPrintOperation *operation, GtkPrintContext *context, gpointer user_data );
void report_dialog( GtkMenuItem *_mi, gpointer _data );

gboolean load_options();
void options_dialog( GtkMenuItem *_mi, gpointer _data );
void about_dialog( GtkMenuItem *_mi, gpointer _data );
void dialog_response (GtkDialog *_dialog, gint _id, gpointer user_data);
gboolean difference_changed( GtkWidget *_widget, GdkEvent  *_event, gpointer   user_data );
gboolean dta_changed( GtkWidget *_widget, GdkEvent  *_event, gpointer   user_data );
void color1_changed( GtkColorButton *_widget, gpointer   user_data );
void color2_changed( GtkColorButton *_widget, gpointer   user_data );

gboolean compare_doses( gdouble _d1, gdouble _d2, gdouble _sensitivity );
gdouble abs1( gdouble );
gint get_number_of_good_points_in_array( GArray* _g );
point find_point_in_garray( GArray* _g, gdouble _x, gdouble _s );//we give x value and function
                                                          // returns dose for given x from _g, _s is sensitivity
gdouble check_dta( GArray* , point* ); //we check the point 
                                                   //from _checked_garray_trimmed against _second garray points,
                                                   //according to defined agreements
gdouble get_step_of_garray( GArray* );
gdouble normalize_garray(  GArray*, guint _graph_type, guint _norm_type );
gdouble max_x_from_garray( GArray* );
gdouble min_x_from_garray( GArray* );
static void msg( const gchar * );
gboolean is_it_number( const gchar * );
void draw_garray( GArray*, GArray*, guint, guint, guint, guint, cairo_t*, gboolean );

void open_omnipro_csv_clicked(  );
void get_omnipro_dataset_clicked(  );
void compare_button_clicked(  );

void monaco_da_draw( GtkWidget *_widget, cairo_t *_cr, gpointer _data );
void omnipro_da_draw( GtkWidget *_widget, cairo_t *_cr, gpointer _data );
void compare_da_draw( GtkWidget *_widget, cairo_t *_cr, gpointer _data );

gboolean compare_da_press (GtkWidget *_widget, GdkEvent  *_event, gpointer   user_data);

void main_quit(  );

#endif /* MAIN_WINDOW_H */
