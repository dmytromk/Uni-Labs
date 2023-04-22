#Завантажуємо бібліотеки
library("psych")
library(moments)

#Считуємо інформацію з csv-файлу
information <- read.csv2(file = 'C:/Users/Dima/univer/Andan/human_development.csv', dec = '.')
colnames(information) = c('hdi_rank','country','hdi_index','life_expectancy', 
                          'expected_years_education', 'mean_years_education',
                          'gni_per_capita', 'gni_rank')

#Логарифмуємо ВНП (Валовий Національник Прибуток)
information[['gni_per_capita']] <- log(information[['gni_per_capita']])

hdi_score <-sort(information[["hdi_index"]])
log_gni <- sort(information[["gni_per_capita"]])
life_expectancy <- sort(information[["life_expectancy"]])
expected_years_education <- sort(information[["expected_years_education"]])


#Емпіричні функції щільності
plot(density(hdi_score), 
     col="red", 
     lwd=2, 
     xlab="HDI Score", 
     main="Емпірична функція щільності для Human Development Index", 
     cex.main=1.4)

plot(density(log_gni), 
     col="green", 
     lwd=2, 
     xlab="Logged GNI per capita", 
     main="Емпірична функція щільності для Logged GNI per capita", 
     cex.main=1.4)

plot(density(life_expectancy), 
     col="blue", 
     lwd=2, 
     xlab="Age", 
     main="Емпірична функція щільності для Life expectancy", 
     cex.main=1.4)

plot(density(expected_years_education), 
     col="purple", 
     lwd=2, 
     xlab="Years", 
     main="Емпірична функція щільності для Expected years of education", 
     cex.main=1.4)


#Полігони частот
hist(hdi_score)
h1 <- hist(hdi_score, xlab="HDI Score", main="Полігон частот для Human Development Index", cex.main=1.5)
lines(h1$counts ~ h1$mids, col="red", lwd=2)

hist(log_gni)
h2 <- hist(log_gni, xlab="Logged GNI per capita", main ="Полігон частот для Logged GNI per capita", cex.main=1.5)
lines(h2$counts ~ h2$mids, col="green", lwd=2)

hist(life_expectancy)
h3 <- hist(life_expectancy, xlab="Age", main="Полігон частот для Life expectancy", cex.main=1.5)
lines(h3$counts ~ h3$mids, col="blue", lwd=2)

hist(expected_years_education)
h4 <- hist(expected_years_education, xlab="Age", main="Полігон частот для Expected years of education", cex.main=1.5)
lines(h4$counts ~ h4$mids, col="purple", lwd=2)


#Скринька з вусами
boxplot(hdi_score, 
        col="red", 
        xlab="HDI Score", 
        main="Скринька з вусами для HDI Score", 
        cex.main=1.5, 
        border=4, 
        horizontal = TRUE, 
        notch=TRUE)

boxplot(log_gni, 
        col="green", 
        xlab="Logged GNI per capita", 
        main="Скринька з вусами для Logged GNI per capita", 
        cex.main=1.5, 
        border=4, 
        horizontal = TRUE, 
        notch=TRUE)

boxplot(life_expectancy, 
        col="blue", 
        xlab="Age", 
        main="Скринька з вусами для Life expectancy", 
        cex.main=1.5, 
        border=4, 
        horizontal = TRUE, 
        notch=TRUE)

boxplot(expected_years_education, 
        col="purple", 
        xlab="Years", 
        main="Скринька з вусами для Expected years of education", 
        cex.main=1.5, 
        border=4, 
        horizontal = TRUE, 
        notch=TRUE)


#Вибіркові значення
empirical <- function(x) {
  print(summary(x))
  cat("Інтерквартильна широта: ", quantile(x, probs=0.75) - quantile(x, probs=0.25), "\n")
  cat("Інтердецильна широта: ", quantile(x, probs=0.9) - quantile(x, probs=0.1), "\n")
  cat("Інтерсектильна широта: ", quantile(x, probs=(5/6)) - quantile(x, probs=(1/6)), "\n")
  cat("\nДецилі:\n")
  quantile(x, probs=seq(0.1, 1, by=0.1))
}

#Вибіркові значення для змінної hdi_score
empirical(hdi_score)

#Вибіркові значення для змінної log_gni
empirical(log_gni)

#Вибіркові значення для змінної life_expectancy
empirical(life_expectancy)

#Вибіркові значення для змінної expected_years_education
empirical(expected_years_education)


#Функція обчислення моди
find_modes<- function(x) {
  dens = density(x)
  modes <- NULL
  for ( i in 2:(length(dens$y)-1) ){
    if ( (dens$y[i] > dens$y[i-1]) & (dens$y[i] > dens$y[i+1]) ) {
      modes <- c(modes,i)
    }
  }
  if ( length(modes) == 0 ) {
    modes = 'Це монотонний розподіл'
    return(modes)
  }
  else {
    return(dens$x[modes])
  }
}

#Функція обчислення характеристик положення центру
empirical_center <- function(x) {
  cat("Математичне сподівання: ", mean(x), "\n")
  cat("Середнє геометричне: ", exp(mean(log(x))), "\n")
  cat("Середнє гармонійне: ", harmonic.mean(x), "\n")
  cat("Мода: ", find_modes(x), "\n")
  cat("Медіана: ", median(x), "\n")
}

#Положення центру для змінної hdi_score
empirical_center(hdi_score)

#Положення центру для змінної log_gni
empirical_center(log_gni)

#Положення центру для змінної life_expectancy
empirical_center(life_expectancy)

#Положення центру для змінної expected_years_education
empirical_center(expected_years_education)


#Характеристики розсіювання значень змінної
empirical_disp <- function(x) {
  cat("Дисперсія: ", var(x), "\n")
  cat("Стандартне відхилення: ", sqrt(var(x)), "\n")
  cat("Коефіцієнт варіації: ", sqrt(var(x))/mean(x), "\n")
  cat("Ймовірнісне відхилення: ", 1/2*(quantile(x, probs=0.75) - quantile(x, probs=0.25)), "\n")
  cat("Розмах вибірки: ", max(x) - min(x), "\n")
  cat("Інтервал концентрації: ",c(mean(x) - 3*sqrt(var(x)), mean(x) + 3*sqrt(var(x))), "\n")
}

#Характеристики розсіювання для змінної hdi_score
empirical_disp(hdi_score)

#Характеристики розсіювання для змінної log_gni
empirical_disp(log_gni)

#Характеристики розсіювання для змінної life_expectancy
empirical_disp(life_expectancy)

#Характеристики розсіювання для змінної expected_years_education
empirical_disp(expected_years_education)


#Функція коефіцієнту асиметрії
asymmetry_coef <- function(x) {
  n = length(x)
  M = mean(x)
  (sum((x - M)^3)/n)/(sum((x-M)^2)/n)^(3/2)
}

#Функція коефіцієнту ексцессу
excess_coef <- function(x) {
  n = length(x)
  M = mean(x)
  (sum((x - M)^4)/n)/(((sum((x-M)^2)/n)^2))-3
}

#Функція виводу асиметрії і ексцессу
asy_exc_print <- function(x) {
  cat("Коефіцієнт асиметрії: ", asymmetry_coef(x), "\n")
  cat("Коефіцієнт ексцессу: ", excess_coef(x), "\n")
}

#Коефіцієнти асиметрії і ексцессу для змінної hdi_score
asy_exc_print(hdi_score)

#Коефіцієнти асиметрії і ексцессу для змінної log_gni
asy_exc_print(log_gni)

#Коефіцієнти асиметрії і ексцессу для змінної life_expectancy
asy_exc_print(life_expectancy)

#Коефіцієнти асиметрія і ексцессу для змінної expected_years_education
asy_exc_print(expected_years_education)


#q-q plot для змінної hdi_score
qqnorm(hdi_score, main = "Q-Q Plot для для Human Development Index", 
       xlab = "Теоретичні квантилі", 
       ylab = "Вибіркові квантилі", col="red")
qqline(hdi_score, lwd = 2)

#q-q plot для змінної log_gni
qqnorm(log_gni, main = "Q-Q Plot для Logged GNI per capita",
       xlab = "Теоретичні квантилі", 
       ylab = "Вибіркові квантилі", col="red")
qqline(log_gni, lwd = 2)

#q-q plot для змінної life_expectancy
qqnorm(life_expectancy, main = "Q-Q Plot для Life expectancy",
       xlab = "Теоретичні квантилі", 
       ylab = "Вибіркові квантилі", col="red")
qqline(life_expectancy, lwd = 2)

#q-q plot для змінної expected_years_education
qqnorm(expected_years_education, main = "Q-Q Plot для Expected years of education",
       xlab = "Теоретичні квантилі", 
       ylab = "Вибіркові квантилі", col="red")
qqline(expected_years_education, lwd = 2)