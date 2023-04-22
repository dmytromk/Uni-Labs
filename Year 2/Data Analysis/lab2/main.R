#Завантажуємо бібліотеки
library("psych")
library(moments)
library(corrplot)
library(irr)
library(nortest)

#Зчитуємо інформацію з csv-файлу
information <- read.csv2(file = 'C:/Users/Dima/univer/Andan/human_development.csv', dec = '.')
colnames(information) = c('hdi_rank','country','hdi_index','life_expectancy', 
                          'expected_years_education', 'mean_years_education',
                          'gni_per_capita', 'gni_rank')

#Логарифмуємо ВНП (Валовий Національник Прибуток)
information[['gni_per_capita']] <- log(information[['gni_per_capita']])

#Знаходимо всі аномалії
get_outliers = function(x){
  q1 = quantile(x, probs=0.25)
  q3 = quantile(x, probs=0.75)
  IQR = IQR(x)
  lower_boundry =  q1 - 1.5*IQR
  upper_boundry =  q3 + 1.5*IQR
}

outliers <- c(get_outliers(information[['hdi_index']]), 
              get_outliers(information[['gni_per_capita']]),
              get_outliers(information[['life_expectancy']]))

#Якщо кількість аномалій > 0, то видяляємо їх
if(length(outliers) > 0)
  information <- information[-outliers,]

hdi_score <-information[["hdi_index"]]
log_gni <- information[["gni_per_capita"]]
life_expectancy <- information[["life_expectancy"]]


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


#Перевіряємо на нормальність
shapiro.test(hdi_score)
shapiro.test(log_gni)
shapiro.test(life_expectancy)

pearson.test(hdi_score)
pearson.test(log_gni)
pearson.test(life_expectancy)


#Аналіз парних зв'язків
ranks = data.frame(rank(hdi_score), rank(log_gni), rank(life_expectancy))

#Спірмен
spearman_pair = cor(ranks, y = NULL, method = "spearman")
corrplot(spearman_pair, method = "number")
cor.test(rank(hdi_score), rank(log_gni), method="spearman", exact = FALSE)
cor.test(rank(hdi_score), rank(life_expectancy), method="spearman", exact = FALSE)
cor.test(rank(log_gni), rank(life_expectancy), method="spearman", exact = FALSE)

#Кенделл
kendall_pair = cor(ranks, y = NULL, method = "kendall")
corrplot(kendall_pair, method = "number")
cor.test(rank(hdi_score), rank(log_gni), method="kendall", exact = FALSE)
cor.test(rank(hdi_score), rank(life_expectancy), method="kendall", exact = FALSE)
cor.test(rank(log_gni), rank(life_expectancy), method="kendall", exact = FALSE)


#Аналіз множинних зв'язків
p_from_model <- function(model) {
  f_value <- summary(model)$fstatistic
  p_value <- pf(f_value[1], f_value[2], f_value[3],lower.tail=F)
  attributes(p_value) <- NULL
  return(p_value)
}

#Зв'язок hdi_score з парою log_gni і life_expectancy
score_to_gni_expect = lm(hdi_score ~ log_gni + life_expectancy)
summary(score_to_gni_expect)$adj.r.squared #множинний коефіцієнт детермінації
p_from_model(score_to_gni_expect)

#Зв'язок log_gni з парою hdi_score і life_expectancy
gni_to_score_expect = lm(log_gni ~ hdi_score + life_expectancy)
summary(gni_to_score_expect)$adj.r.squared #множинний коефіцієнт детермінації
p_from_model(gni_to_score_expect)

#Зв'язок life_expectancy з парою log_gni і hdi_score
expect_to_gni_score = lm(life_expectancy ~ log_gni + hdi_score)
summary(expect_to_gni_score)$adj.r.squared #множинний коефіцієнт детермінації
p_from_model(expect_to_gni_score)