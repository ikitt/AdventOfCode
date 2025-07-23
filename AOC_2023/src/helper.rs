pub fn int_str_to_int(int_str: String) -> Vec<u8> {
    let int_str_trime: String = int_str.trim().to_string();
    println!("Will split and map '{}'", int_str_trime);
    int_str_trime
        .split_whitespace()
        .map(|one_int_str| one_int_str.parse::<u8>().unwrap())
        .collect::<Vec<u8>>() //).collect::<Vec<&str>>()[1].to_string();
}
