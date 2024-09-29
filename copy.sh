#!/bin/bash

scp -p22 /home/gitlab-runner/builds/1pCZ-7z4/0/students/DO6_CICD.ID_356283/miklazru_student.21_school.ru/DO6_CICD-1/src/cat/s21_cat matthew_ubuntu_test@10.10.0.2:~/
scp -p22 /home/gitlab-runner/builds/1pCZ-7z4/0/students/DO6_CICD.ID_356283/miklazru_student.21_school.ru/DO6_CICD-1/src/grep/s21_grep matthew_ubuntu_test@10.10.0.2:~/

ssh matthew_ubuntu_test@10.10.0.2 "echo 5656000 | sudo -S mv s21_cat /usr/local/bin"
ssh matthew_ubuntu_test@10.10.0.2 "echo 5656000 | sudo -S mv s21_grep /usr/local/bin"

