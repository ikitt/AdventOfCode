// ikitt for Advent of Code 2023

use std::cmp::Ordering;
use std::collections::HashMap;
use std::fs::read_to_string;
use std::usize;

#[derive(Eq)]
struct Star {
    row: usize,
    col: usize,
    neighbors: Vec<u64>,
}

impl Star {
    // A constructor to create a new Star for part 2
    fn new(row_in: usize, col_in: usize) -> Star {
        Star {
            row: row_in,
            col: col_in,
            neighbors: vec![],
        }
    }

    // An instance method
    fn add_neighbor(&mut self, neighbor: u64) {
        self.neighbors.push(neighbor);
    }
}

impl Ord for Star {
    fn cmp(&self, other: &Self) -> Ordering {
        if self.row == other.row {
            self.col.cmp(&other.col)
        } else {
            self.row.cmp(&other.row)
        }
    }
}

impl PartialOrd for Star {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl PartialEq for Star {
    fn eq(&self, other: &Self) -> bool {
        self.row == other.row && self.col == other.col
    }
}

pub fn compute_part_1() -> u64 {
    let mut res: u64 = 0;
    let input_path: &str = "./input/y23_d03_in.txt"; // give 539590
                                                     // let input_path: &str = ".\\input\\y23_d03_test1.txt"; // give 4361

    let table: Vec<Vec<char>> = input_as_table(input_path);

    for (row, line) in table.iter().enumerate() {
        let mut current_number: u64 = 0;
        let mut is_number: bool = false;
        let mut is_valid_number: bool = false;
        for (col, ch) in line.iter().enumerate() {
            if table[row][col].is_ascii_digit() {
                is_number = true;
                current_number =
                    current_number * 10 + u64::from(table[row][col].to_digit(10).unwrap());
                if !(is_valid_number) && has_symbol_neighbor(row, col, &table) {
                    // println!("first valid {row} {col}");
                    is_valid_number = true;
                }
            } else {
                if is_number && !is_valid_number {
                    // println!("c {current_number}; valid {is_valid_number}");
                }
                if is_valid_number {
                    res = res + current_number;
                }
                is_number = false;
                current_number = 0;
                is_valid_number = false;
            }
        }
        if is_valid_number {
            res = res + current_number;
        }
    }

    return res; // res is 539590
}

pub fn compute_part_2() -> u64 {
    /*
    Analyse des nombres
    Pour chaque nombre sauvegarder les étoiles adjacentes
    Créer une struct pour chaque étoile avec la position et les nombres adjacents
    Stocker ces structs dans une HashMap <positon, struct>
        Si la position est déjà connu, ajouter le nombre courant
        Sinon créé la struct et la poussé dans la HashMap
    Analyser toutes les structs, celle qui ont exactement 2 nombres adjacents doivent être incluse dans le résultats.
     */

    let mut res: u64 = 0;
    let input_path: &str = "./input/y23_d03_in.txt"; // 80703636 is the result.

    // let input_path: &str = "./input/y23_d03_test1.txt"; // give 467835

    let table: Vec<Vec<char>> = input_as_table(input_path);
    println!("Table: {:#?}", table);
    let mut star_map: HashMap<(usize, usize), Star> = HashMap::new();

    let mut star_pos_list: Vec<(usize, usize)> = vec![];
    for (row, line) in table.iter().enumerate() {
        let mut current_number: u64 = 0;
        let mut is_number: bool = false;
        for (col, ch) in line.iter().enumerate() {
            if table[row][col].is_ascii_digit() {
                is_number = true;
                current_number =
                    current_number * 10 + u64::from(table[row][col].to_digit(10).unwrap());

                add__stars_pos_to_list(row, col, &table, &mut star_pos_list);
                if col == line.len() - 1 {
                    // End of line
                    store_number_in_star(
                        row,
                        col,
                        current_number,
                        &mut star_pos_list,
                        &mut star_map,
                    );
                }
            } else {
                if is_number {
                    // End of a number
                    store_number_in_star(
                        row,
                        col,
                        current_number,
                        &mut star_pos_list,
                        &mut star_map,
                    );
                }
                is_number = false;
                current_number = 0;
            }
        }
    }

    let mut stars_vec: Vec<Star> = vec![]; // for DEBUG
    for (pos, star) in star_map.into_iter() {
        stars_vec.push(star);
    }

    println!("First star count is {}", stars_vec.len());

    stars_vec.sort();
    stars_vec.dedup();

    println!("Second star count is {}", stars_vec.len());

    for star in stars_vec.iter() {
        // print!(
        //     "Star at pos {:?}, has neighbor {:?} ",
        //     (star.row, star.col),
        //     star.neighbors
        // );
        if star.neighbors.len() == 2 {
            res += star.neighbors[0] * star.neighbors[1];
            // println!(" v => {res}");
        } else {
            // println!(" x");
        }
    }

    // print_gear(&stars_vec);

    res
}

fn store_number_in_star(
    row: usize,
    col: usize,
    current_number: u64,
    star_pos_list: &mut Vec<(usize, usize)>,
    mut star_map: &mut HashMap<(usize, usize), Star>,
) {
    star_pos_list.sort();
    star_pos_list.dedup();

    println!(
        "Read number {} at ({},{}) which has {} stars as neighbors.",
        current_number,
        row,
        col,
        star_pos_list.len()
    );

    star_pos_list
        .clone()
        .into_iter()
        .for_each(|star_pos: (usize, usize)| {
            create_or_push_star(&star_pos, current_number, &mut star_map);
        });
    star_pos_list.clear();
}

fn input_as_table(input_pth: &str) -> Vec<Vec<char>> {
    let mut table: Vec<Vec<char>> = vec![];
    for line in read_to_string(input_pth).unwrap().lines() {
        let mut table_line: Vec<char> = vec![];
        for ch in line.chars() {
            table_line.push(ch)
            // print!("row {row_id} col {col_id} char {ch};");
        }
        table.push(table_line);
        // println!("");
    }
    // println!("{:?}", table); // Debug print
    return table;
}

fn has_symbol_neighbor(row: usize, col: usize, table: &Vec<Vec<char>>) -> bool {
    let max_row = table.len() - 1;
    let max_col = table[0].len() - 1;

    if row > 0 && is_symbor(table[row - 1][col]) {
        return true;
    }
    if row < max_row && is_symbor(table[row + 1][col]) {
        return true;
    }
    if col > 0 && is_symbor(table[row][col - 1]) {
        return true;
    }
    if col < max_col && is_symbor(table[row][col + 1]) {
        return true;
    }
    if row > 0 && col > 0 && is_symbor(table[row - 1][col - 1]) {
        return true;
    }
    if row > 0 && col < max_col && is_symbor(table[row - 1][col + 1]) {
        return true;
    }
    if row < max_row && col > 0 && is_symbor(table[row + 1][col - 1]) {
        return true;
    }

    if row < max_row && col < max_col && is_symbor(table[row + 1][col + 1]) {
        return true;
    }
    false
}

fn add__stars_pos_to_list(
    row: usize,
    col: usize,
    table: &Vec<Vec<char>>,
    star_pos_list: &mut Vec<(usize, usize)>,
) {
    let max_row = table.len() - 1;
    let max_col = table[0].len() - 1;

    let row_i32 = row as i32;
    let col_i32 = col as i32;
    if is_star(table, row_i32 - 1, col_i32) {
        star_pos_list.push((row - 1, col));
    }
    if is_star(table, row_i32 + 1, col_i32) {
        star_pos_list.push((row + 1, col));
    }
    if is_star(table, row_i32, col_i32 - 1) {
        star_pos_list.push((row, col - 1));
    }
    if is_star(table, row_i32, col_i32 + 1) {
        star_pos_list.push((row, col + 1));
    }
    if is_star(table, row_i32 - 1, col_i32 - 1) {
        star_pos_list.push((row - 1, col - 1));
    }
    if is_star(table, row_i32 - 1, col_i32 + 1) {
        star_pos_list.push((row - 1, col + 1));
    }
    if is_star(table, row_i32 + 1, col_i32 - 1) {
        star_pos_list.push((row + 1, col - 1));
    }
    if is_star(table, row_i32 + 1, col_i32 + 1) {
        star_pos_list.push((row + 1, col + 1));
    }
}

fn is_symbor(ch: char) -> bool {
    let is_dig: bool = ch.is_digit(10);
    let is_point: bool = ch == '.';
    return !(is_dig || is_point);
}

/// Check if there is a star at (rox_i32, col_i32) in table
fn is_star(table: &Vec<Vec<char>>, row_i32: i32, col_i32: i32) -> bool {
    if row_i32 >= table.len() as i32
        || col_i32 >= table[0].len() as i32
        || row_i32 < 0
        || col_i32 < 0
    {
        // always use table[0].len to ensure validity
        return false;
    }
    // println!("row {} col {}", row_i32, col_i32);
    // println!("table[row] {:#?}", table[row_i32 as usize]);
    // println!("Table: {:#?}", table);
    table[row_i32 as usize][col_i32 as usize] == '*'
}

/// Create a new star if wasn't one at star_pos, and push the current number to the star
fn create_or_push_star(
    star_pos: &(usize, usize),
    current_number: u64,
    star_map: &mut HashMap<(usize, usize), Star>,
) {
    if !star_map.contains_key(star_pos) {
        star_map.insert(
            star_pos.clone(),
            Star::new(star_pos.0.clone(), star_pos.1.clone()),
        );
    }
    star_map
        .get_mut(star_pos)
        .unwrap()
        .neighbors
        .push(current_number.clone());
}

/// Print 'v' for gear and 'x' for other star, other symbol printed as ' '
fn print_gear(star_Vec: &Vec<Star>) {
    let mut current_row = 0;
    let mut current_col = 0;
    for star in star_Vec.iter() {
        if current_row < star.row {
            current_col = 0;
        }
        for _ in current_row..star.row {
            println!();
        }
        current_row = star.row;
        for _ in current_col..star.col {
            print!(" ");
        }
        if star.neighbors.len() == 2 {
            print!("v");
        } else {
            print!("x");
        }
        current_col = star.col + 1;
    }
}
