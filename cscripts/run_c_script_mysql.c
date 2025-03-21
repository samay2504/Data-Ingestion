#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <prog_run>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int prog_run = atoi(argv[1]);

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    // Connect to MySQL server
    if (mysql_real_connect(conn, "127.0.0.1", "root", "strong_password", "travel_lab_2_dp_5", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Record the start time
    clock_t start_time = clock();

    if (prog_run == 0) {
        // Execute SQL query
        if (mysql_query(conn, "SELECT C.car_number, C.type FROM Booking B JOIN Car C ON B.car_id = C.car_id WHERE YEAR(B.booking_date) = 2023")) {
            fprintf(stderr, "SELECT * FROM your_table failed. Error: %s\n", mysql_error(conn));
            mysql_close(conn);
            return EXIT_FAILURE;
        }

    } else if (prog_run == 1) {
        // Execute SQL query
        if (mysql_query(conn, "SELECT C.car_number, C.type FROM Booking B JOIN Car C ON B.car_id = C.car_id WHERE YEAR(B.booking_date) = 2023 AND B.flight_id IS NOT NULL")) {
            fprintf(stderr, "SELECT * FROM your_table failed. Error: %s\n", mysql_error(conn));
            mysql_close(conn);
            return EXIT_FAILURE;
        }

    } else if (prog_run == 2) {
        // Execute SQL query
        if (mysql_query(conn, "SELECT u.username, u.contact_info, u.email FROM Users u JOIN Booking b ON u.user_id = b.user_id JOIN Hotel h ON b.hotel_id = h.hotel_id JOIN Car c ON b.car_id = c.car_id WHERE h.name = 'Hotel Plaza' AND c.model = 'Toyota Corolla' AND YEAR(b.booking_date) = 2022")) {
            fprintf(stderr, "SELECT * FROM your_table failed. Error: %s\n", mysql_error(conn));
            mysql_close(conn);
            return EXIT_FAILURE;
        }

    } else {
        fprintf(stderr, "Invalid value for prog_run. Use 0, 1, or 2.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Store the result of the query
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Record the end time
    clock_t end_time = clock();

    // Calculate the time taken for the query execution
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Query executed in %f seconds\n", time_taken);

    // Print the result
    int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    // Free the result set
    mysql_free_result(res);

    // Close the connection
    mysql_close(conn);

    return EXIT_SUCCESS;
}
