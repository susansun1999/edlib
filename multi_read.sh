#!/bin/bash

# Number of iterations
iterations=$((64))

# Command to execute
#command="./cal_ed test_data/Enterobacteria_Phage_1_100k/Enterobacteria_phage_1.fasta test_data/Enterobacteria_Phage_1_100k/mutated_99_perc.fasta"


#command="./cal_ed test_data/E_coli_DH1/mason_illumina_reads/10kbp/e_coli_DH1_illumina_1x10000.fasta  test_data/E_coli_DH1/mason_illumina_reads/10kbp/mutated_97_perc.fasta"

command="./cal_ed test_data/E_coli_DH1/mason_illumina_reads/50bp/e_coli_DH1_illumina_1x50.fasta test_data/E_coli_DH1/mason_illumina_reads/50bp/mutated_97_perc.fasta"

#command="./cal_ed test_data/E_coli_DH1/mason_illumina_reads/500bp/e_coli_DH1_illumina_1x50.fasta test_data/E_coli_DH1/mason_illumina_reads/500bp/mutated_97_perc.fasta"

# Loop to start the command concurrently

for ((i = 1; i <= $iterations; i++)); do
#    echo "Starting concurrent iteration $i..."
    $command &
done

# Wait for all background processes to complete
wait

#echo "All $iterations commands have been executed concurrently!"

