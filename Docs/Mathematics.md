## !READ WITH LATEX INTERPRETER!

In order to get familiar with the mathematics used in raytracing, I've designed this step by step guide in understanding
the linear algebra. \
We'll talk about the mathematics in 3D/4D space.

Refer to the examples at the bottom of the page for more intuitive understanding.

# Table of contents

- [Symbols](#symbols)
- [Generic 3D object](#generic-3d-object)
  - [3D addition](#3d-addition)
  - [3D subtraction](#3d-subtraction)
  - [3D multiplication](#3d-multiplication)
  - [3D division](#3d-division)
- [Vector operations](#vector-operations)
    - [Magnitude/Length](#magnitudelength)
    - [Normalization](#normalization)
    - [Dot product](#dot-product)
    - [Cross product](#cross-product)
    - [Angle between vectors](#angle-between-vectors)
    - [Reflection](#reflection)
    - [Refraction](#refraction)
- [Point operations](#point-operations)
    - [Point to vector](#point-to-vector)
    - [Center](#center)
    - [Distance](#distance)
- [Examples](#examples)
    - [3D addition](#3d-addition-1)
    - [3D subtraction](#3d-subtraction-1)
    - [3D multiplication](#3d-multiplication-1)
    - [3D division](#3d-division-1)
    - [Magnitude/Length](#magnitudelength-1)
    - [Normalization](#normalization-1)
    - [Dot product](#dot-product-1)
    - [Cross product](#cross-product-1)

# Symbols

Please refer to the [wiki](https://en.wikipedia.org/wiki/List_of_mathematical_symbols_by_subject) for all of the
symbols. \
Symbols used in this document:

| Symbol          | Meaning                                                                  | Description                                                                                   |
|-----------------|--------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| $\mathbb{R}$    | [Real numbers](https://en.wikipedia.org/wiki/Real_number)                | Real numbers are all numbers that can be written on a number line.                            |
| $\mathbb{R}^n$  | Real numbers in n-dimensional space                                      | Real numbers in n-dimensional space.                                                          |
| $\vec{v}$       | [Vector](https://en.wikipedia.org/wiki/Vector_(mathematics_and_physics)) | A vector is a line that starts at the origin and points somewhere.                            |
| $\hat{v}$       | [Unit vector](https://en.wikipedia.org/wiki/Unit_vector)                 | A unit vector is a vector with a length of 1.                                                 |
| $\pi$           | [Pi](https://en.wikipedia.org/wiki/Pi)                                   | Pi is a mathematical constant (3.14...)                                                       |
| $\theta\degree$ | [Angle in degrees](https://en.wikipedia.org/wiki/Degree_(angle))         | Angle in degrees (0 - 360).                                                                   |
| $\theta_{rad}$  | [Angle in radians](https://en.wikipedia.org/wiki/Radian)                 | Angle in radians (0 - $2\pi$).                                                                |
| $\degree$       | Degree                                                                   | Degree symbol.                                                                                |
| $\angle$        | [Angle](https://en.wikipedia.org/wiki/Angle)                             | Angle symbol.                                                                                 |
| $\parallel$     | [Parallel](https://en.wikipedia.org/wiki/Parallel_(geometry))            | A parallel object is pointing in the same direction as another.                               |
| $\perp$         | [Perpendicular](https://en.wikipedia.org/wiki/Orthogonality)             | A perpendicular object is pointing in a 90 degree angle.                                      |
| $\cdot$         | [Dot product](https://en.wikipedia.org/wiki/Dot_product)                 | Dot product is a way to calculate the angle between two vectors.                              |
| $\times$        | [Cross product](https://en.wikipedia.org/wiki/Cross_product)             | Cross product is a way to calculate a vector perpendicular to two other vectors.              |
| $\leq$          | Less than or equal to                                                    | Less than or equal to means that the left side is less than or equal to the right side.       |
| $\geq$          | Greater than or equal to                                                 | Greater than or equal to means that the left side is greater than or equal to the right side. |
| $\triangleq$    | Equivalent by definition                                                 | Equivalent means that the left side is equal to the right side.                               |
| $\Rightarrow$   | Logical consequence                                                      | Logical consequence means that the properties of the right side are true for the left side.   |

# [Generic 3D object](https://github.com/BardoBard/Bardrix/blob/master/Bardrix/include/bardrix/dimension3.h)

Let's start with definitions, don't be intimidated by the math, it's not as hard as it looks. \
Later on in the examples you'll see that it's actually quite simple.

$$
\vec{v} =
\begin{bmatrix}
x \\
y \\
z \\
\end{bmatrix}
$$

This is a 3D object, it has 3 components, x, y and z. As you can see, we write vectors with a little arrow on top of the
name.

Usually with 3D objects we use $\mathbb{R}^3$, which means that the components are real numbers, but also in 3D space. \
I'll be using the notation $\mathbb{R}^3$ a lot, so it's important to understand what it means.

## [3D addition](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fdimension3.h+operator%2B&type=code)

We can add two $\mathbb{R}^3$ objects together, this is called addition. Here the $x_1$ $y_1$ $z_1$ get added to $x_2$
$y_2$ $z_2$
respectively.

$$
\vec{v}_1 + \vec{v}_2 = \vec{v}_3 \triangleq
\begin{bmatrix}
x_1 \\
y_1 \\
z_1 \\
\end{bmatrix} +
\begin{bmatrix}
x_2 \\
y_2 \\
z_2 \\
\end{bmatrix} =
\begin{bmatrix}
x_1 + x_2 \\
y_1 + y_2 \\
z_1 + z_2 \\
\end{bmatrix}
$$

## [3D subtraction](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fdimension3.h+operator-&type=code)

We can also subtract $\mathbb{R}^3$ objects from each other, this is called subtraction.

$$
\vec{v}_1 - \vec{v}_2 = \vec{v}_3 \triangleq
\begin{bmatrix}
x_1 \\
y_1 \\
z_1 \\
\end{bmatrix} -
\begin{bmatrix}
x_2 \\
y_2 \\
z_2 \\
\end{bmatrix} =
\begin{bmatrix}
x_1 - x_2 \\
y_1 - y_2 \\
z_1 - z_2 \\
\end{bmatrix}
$$

## [3D multiplication](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fdimension3.h+operator*&type=code)

An $\mathbb{R}^3$ can't be multiplied by another $\mathbb{R}^3$, there is no definition for that. \
However, we can multiply an $\mathbb{R}^3$ by a number, this number is called a scalar.

$$
\vec{v}_1 * n =
\begin{bmatrix}
x_1 \\
y_1 \\
z_1 \\
\end{bmatrix} * n =
\begin{bmatrix}
x_1 * n \\
y_1 * n \\
z_1 * n \\
\end{bmatrix}
$$

## [3D division](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fdimension3.h+operator/&type=code)

Just like multiplication, we have to use scalar division.

$$
\frac{\vec{v}_1}{n} =
\begin{bmatrix}
x_1 \\
y_1 \\
z_1 \\
\end{bmatrix} / n =
\begin{bmatrix}
\frac{x_1}{n} \\
\frac{y_1}{n} \\
\frac{z_1}{n} \\
\end{bmatrix}
$$

---

# [Vector operations](https://github.com/BardoBard/Bardrix/blob/master/Bardrix/include/bardrix/vector3.h)

Vectors start at the origin and points to a position in space. \
Vectors are written with a little arrow on top of the name, like this: $\vec{v}$.

## [Magnitude/Length](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fvector3.h+length&type=code)

Vectors have a few operations that are unique to them. \
One of them is calculating the magnitude of a vector, this is also called the length of a vector.

The magnitude of a vector is always a positive number.

$$
||\vec{v}|| = |\vec{v}| =
\sqrt{x^2 + y^2 + z^2}
$$

Sometimes you'll see the magnitude of a vector written with double bars, this is just a different notation. \
I'll be using the single bar notation, but it's important to know that they mean the same thing.

An optimization that can be done is to square the magnitude of a vector to avoid using the square root function.

$$
||\vec{v}||^2 = |\vec{v}|^2 =
x^2 + y^2 + z^2
$$

It's important to understand that the result of the magnitude of a vector is the size of the vector, which is a number.

## [Normalization](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fvector3.h+normalize&type=code)

Now that we know how to calculate the magnitude of a vector, we can normalize a vector.

Normalization is the process of making a vector have a length of 1, yet the same direction. \
This is used for calculating the angle between two vectors, and a lot more
which we'll see later.

A normalized vector is also called a [unit vector](#symbols), and is written with a little hat on top of the name, like
this:
$\hat{v}$.

$$
\hat{v} =
\frac{\vec{v}}{|\vec{v}|} =
\frac{\vec{v}}{\sqrt{x^2 + y^2 + z^2}} =
\begin{bmatrix}
\frac{x}{\sqrt{x^2 + y^2 + z^2}} \\
\frac{y}{\sqrt{x^2 + y^2 + z^2}} \\
\frac{z}{\sqrt{x^2 + y^2 + z^2}} \\
\end{bmatrix}
$$

Now if we calculate the magnitude of a normalized vector, we get 1.

## [Dot product](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fvector3.h+dot&type=code)

The dot product is a way to calculate the angle between two vectors. \
The dot product is also called the scalar product.

The result of the dot product is a number between -1 and 1.

| Dot product | Definition                       | Explanation                                     | Angle        |
|-------------|----------------------------------|-------------------------------------------------|--------------|
| 1           | $\vec{v}_1 \parallel \vec{v}_2$  | Vectors are pointing in the same direction.     | $0\degree$   |
| 0           | $\vec{v}_1 \perp \vec{v}_2$      | Vectors are perpendicular to each other.        | $90\degree$  |
| -1          | $\vec{v}_1 \parallel -\vec{v}_2$ | Vectors are pointing in the opposite direction. | $180\degree$ |

$$
\vec{v}_1 \cdot \vec{v}_2 = \vec{v}_3 =
\begin{bmatrix}
x_1 \\
y_1 \\
z_1 \\
\end{bmatrix} \cdot
\begin{bmatrix}
x_2 \\
y_2 \\
z_2 \\
\end{bmatrix} =
x_1 * x_2 + y_1 * y_2 + z_1 * z_2
$$

The notation is a literal dot sign, not a multiplication sign. \
The dot product is a scalar, meaning that it's a number.

Dot product is sometimes written as $(\vec{v}_1 , \vec{v}_2)$ instead of $\vec{v}_1 \cdot \vec{v}_2$.

## [Cross product](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fvector3.h+cross&type=code)

The cross product is a way to calculate a vector that is perpendicular $\perp$ ($90\degree$) to two other vectors. \
Naturally this means that the cross product is a vector.

$$
\vec{v}_1 \times \vec{v}_2 = \vec{v}_3 =
\begin{bmatrix}
x_1 \\
y_1 \\
z_1 \\
\end{bmatrix} \times
\begin{bmatrix}
x_2 \\
y_2 \\
z_2 \\
\end{bmatrix} =
\begin{bmatrix}
y_1 * z_2 - z_1 * y_2 \\
z_1 * x_2 - x_1 * z_2 \\
x_1 * y_2 - y_1 * x_2 \\
\end{bmatrix}
$$

You can see the notation is a literal cross sign.

Cross product is sometimes written as $[\vec{v}_1 , \vec{v}_2]$ instead of $\vec{v}_1 \times \vec{v}_2$.

## [Angle between vectors](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fvector3.h+angle&type=code)

Now that we know how to calculate the dot product, we can calculate the angle between two vectors. \
The angle between two vectors is the same as the angle between two lines.

$$
\theta_{rad} = \cos^{-1}(\hat{v}_1 \cdot \hat{v}_2) =
\cos^{-1}(\frac{\vec{v}_1}{|\vec{v}_1|} \cdot \frac{\vec{v}_2}{|\vec{v}_2|})
$$

Here theta $\theta$ is in radians, we can also calculate the angle in degrees.

$$
\theta\degree = \theta_{rad} * \frac{180}{\pi} \triangleq \cos^{-1}(\hat{v}_1 \cdot \hat{v}_2) * \frac{180}{\pi}
$$

That being said, these are slow operations, it's better to use a dot product to calculate the angle between two
vectors. \
Which we've already seen, just make sure to normalize the vectors first.

$$
\hat{v}_1 \cdot \hat{v}_2 \Rightarrow \lbrace-1 \leq \theta \leq 1\rbrace
$$

Like mentioned in the [dot product](#dot-product), only here we normalize both vectors first.

## [Reflection](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fvector3.h+reflection&type=code)

Reflection is a way to calculate the direction of a vector after it bounces off a surface. \
This is used for calculating the direction of a vector after it hits a surface.

$$
Ref_l \(\vec{v}_1, \vec{v}_n\) = \hat{v}_n * \(2 * \vec{v}_1\ \cdot \hat{v}_n) - \vec{v}_1
$$

Here the $\vec{v}_1$ is the direction of the vector, and $\vec{v}_n$ is the normal of the surface. \
This normalizes the normal vector, then calculates the reflection vector. \
You could avoid this assuming $|\vec{v}_n| = 1$, but it's better to normalize the normal regardless.

Important to note that the resulting reflection vector is not normalized, this obviously means that the incoming vector
has the same magnitude as the outgoing vector.

You could extend the definition to where \vec{v}_1\ \cdot \hat{v}_n < 0$ is invalid, this is due to the fact that the
normal is pointing away from the incoming vector. \
This is not necessary, but it's important to know that the normal should be pointing towards the incoming vector. \
Perhaps turn the normal around if this is the case.

## [Refraction](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fvector3.h+refraction&type=code)

Refraction is a way to calculate the direction of a vector after it passes through a surface. \
This can be anything from glass, water, air, etc.

With reference to the [wiki](https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form) we can calculate the refraction
vector.\
We start with the definitions:

$$
r = \frac{n_1}{n_2}
$$

Here $n_1$ and $n_2$ are the [refractive mediums](https://en.wikipedia.org/wiki/List_of_refractive_indices#List), for
example air and glass. \
$r$ is the refractive ratio, which is the ratio between the refractive mediums.

$$
\cos\theta_1 = -\hat{v}_n \cdot \hat{v}_l
$$

This is just a simple dot product between the normal and the incoming vector. \
The reason why it's inverted is that we want the angle between the normal and the incoming vector, not the outgoing.

$$
\sin\theta_2 = \sqrt{1 - r^2 * (1 - (\cos\theta_1)^2)}
$$

This is an important step, now we know the angle of the outgoing vector. \
If the outgoing vector is pointing away from the surface, then the angle is invalid. \
This means that we've got an internal reflection, which we can already calculate with the reflection vector.

This means that if $\sin\theta_2 \geq 1$ then we throw it away:

$$
Ref_r\(\vec{v}_1, \vec{v}_n\, r\) = r * \hat{v}_1 + \hat{v}_n * \(r * \cos\theta_1 - \sqrt{1 - (\sin\theta_2))}\)
\Rightarrow \lbrace\sin\theta_2 < 1\rbrace
$$

This is the final definition, here we calculate the refraction vector.

# [Point operations](https://github.com/BardoBard/Bardrix/blob/master/Bardrix/include/bardrix/point3.h)

Points are very similar to vectors, but they don't have a direction. \
Points are written with a capital letter, like this: $P$.

## [Point to vector](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fpoint3.h+vector_to&type=code)

We can convert a point to a vector, this is done by subtracting the origin from the point.

$$
\vec{V}_{P_2 \rightarrow P_1} = P_1 - P_2 =
\begin{bmatrix}
x_1 \\
y_1 \\
z_1 \\
\end{bmatrix} -
\begin{bmatrix}
x_2 \\
y_2 \\
z_2 \\
\end{bmatrix} =
\begin{bmatrix}
x_1 - x_2 \\
y_1 - y_2 \\
z_1 - z_2 \\
\end{bmatrix}
$$

Important to understand that we're creating a vector that points from $P_2$ to $P_1$. \
The subtraction is the same as any $\mathbb{R}^3$ subtraction.

## [Center](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fpoint3.h+midpoint&type=code)

We can calculate the center of two points, this is done by adding the two points together and dividing by 2. \
This is a pretty simple operation.

$$
P_{center} = \frac{P_1 + P_2}{2} =
\begin{bmatrix}
\frac{x_1 + x_2}{2} \\
\frac{y_1 + y_2}{2} \\
\frac{z_1 + z_2}{2} \\
\end{bmatrix}
$$

## [Distance](https://github.com/search?q=repo%3ABardoBard%2FBardrix+path%3A**%2Fpoint3.h+distance&type=code)

We can calculate the distance between two points. \
This might be useful for calculating the distance between two objects, or a lot of other things.

$$
d =
\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2 + (z_1 - z_2)^2} \Rightarrow \lbrace P_1 \geq P_2 \rbrace
$$

Here $d$ is the distance between $P_1$ and $P_2$. \
$P_1$ has to be greater than $P_2$, otherwise the distance is negative, which can make sense in some cases. Just keep it
in mind while designing your application.

Another optimization that can be done is to square the distance to avoid using the square root function.

$$
d^2 =
(x_1 - x_2)^2 + (y_1 - y_2)^2 + (z_1 - z_2)^2 \Rightarrow \lbrace P_1 \geq P_2 \rbrace
$$

# Examples

## [3D addition](#3d-addition)

$$
\vec{v}_1 + \vec{v}_2 = \vec{v}_3 \triangleq
\begin{bmatrix}
1 \\
2 \\
3 \\
\end{bmatrix} +
\begin{bmatrix}
4 \\
5 \\
6 \\
\end{bmatrix} =
\begin{bmatrix}
1 + 4 \\
2 + 5 \\
3 + 6 \\
\end{bmatrix} =
\begin{bmatrix}
5 \\
7 \\
9 \\
\end{bmatrix}
$$

## [3D subtraction](#3d-subtraction)

$$
\vec{v}_1 - \vec{v}_2 = \vec{v}_3 \triangleq
\begin{bmatrix}
1 \\
2 \\
3 \\
\end{bmatrix} -
\begin{bmatrix}
4 \\
5 \\
6 \\
\end{bmatrix} =
\begin{bmatrix}
1 - 4 \\
2 - 5 \\
3 - 6 \\
\end{bmatrix} =
\begin{bmatrix}
-3 \\
-3 \\
-3 \\
\end{bmatrix}
$$

## [3D multiplication](#3d-multiplication)

$$
\vec{v}_1 * n =
\begin{bmatrix}
1 \\
2 \\
3 \\
\end{bmatrix} * 2 =
\begin{bmatrix}
1 * 2 \\
2 * 2 \\
3 * 2 \\
\end{bmatrix} =
\begin{bmatrix}
2 \\
4 \\
6 \\
\end{bmatrix}
$$

## [3D division](#3d-division)

$$
\frac{\vec{v}_1}{n} =
\begin{bmatrix}
1 \\
2 \\
3 \\
\end{bmatrix} / 2 =
\begin{bmatrix}
\frac{1}{2} \\
\frac{2}{2} \\
\frac{3}{2} \\
\end{bmatrix} =
\begin{bmatrix}
0.5 \\
1 \\
1.5 \\
\end{bmatrix}
$$

## [Magnitude/Length](#magnitudelength)

$$
||\vec{v}|| = |\vec{v}| =
\sqrt{1^2 + 2^2 + 3^2} =
\sqrt{14} \approx 3.74165738677
$$

## [Normalization](#normalization)

$$
Norm
\begin{bmatrix}
1 \\
2 \\
3 \\
\end{bmatrix}
= \hat{v} =
\frac{\vec{v}}{|\vec{v}|} =
\frac{\vec{v}}{\sqrt{1^2 + 2^2 + 3^2}} =
\begin{bmatrix}
\frac{1}{\sqrt{14}} \\
\frac{2}{\sqrt{14}} \\
\frac{3}{\sqrt{14}} \\
\end{bmatrix} \approx
\begin{bmatrix}
0.267261241912 \\
0.534522483825 \\
0.801783725737 \\
\end{bmatrix}
$$

## [Dot product](#dot-product)

$$
\vec{v}_1 \cdot \vec{v}_2 = \vec{v}_3 =
\begin{bmatrix}
1 \\
2 \\
3 \\
\end{bmatrix} \cdot
\begin{bmatrix}
4 \\
5 \\
6 \\
\end{bmatrix} =
1 * 4 + 2 * 5 + 3 * 6 =
4 + 10 + 18 =
32
$$

## [Cross product](#cross-product)

$$
\vec{v}_1 \times \vec{v}_2 = \vec{v}_3 =
\begin{bmatrix}
1 \\
2 \\
3 \\
\end{bmatrix} \times
\begin{bmatrix}
4 \\
5 \\
6 \\
\end{bmatrix} =
\begin{bmatrix}
2 * 6 - 3 * 5 \\
3 * 4 - 1 * 6 \\
1 * 5 - 2 * 4 \\
\end{bmatrix} =
\begin{bmatrix}
12 - 15 \\
12 - 6 \\
5 - 8 \\
\end{bmatrix} =
\begin{bmatrix}
-3 \\
6 \\
-3 \\
\end{bmatrix}
$$