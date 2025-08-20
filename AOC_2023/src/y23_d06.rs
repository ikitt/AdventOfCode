// ikitt for Advent of Code 2023

/// Done on OfficeCalc and notebook
/// With:
///     T : the total time of the race (const)
///     D : the distance you want to beat(const)
///     v : the speed of the boat
///     t : the time the boat race
///     d : the distance reached
///     t valid in [1;T-1]
/// You want : d > D
/// You have
///     d = v*t
///     v = T - t (considering the problem info)
///     => d = (T-t)t
///     ...
///     => t = T/2 +or- sqrt((T*T/4)- d)
/// set d = D to find the range where you beat D (take care as equality is not accepted, might check if boundarie are exact or not)
/// number of solution are the interval size (including boundaries)

pub fn compute_part_1() -> u64 {
    1159152
}

pub fn compute_part_2() -> u64 {
    41513103
}
