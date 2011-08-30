/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

// Algorithm from section 2.14.1 of OpenGL 2.1 specification.

attribute highp vec4 vertex;
attribute highp vec3 normal;
attribute highp vec4 texcoord;
uniform mediump mat4 matrix;
uniform mediump mat4 modelView;
uniform mediump mat3 normalMatrix;
varying highp vec4 qTexCoord;

uniform mediump vec4 scli;      // Specular intensity of the light
uniform mediump vec3 pli;       // Position of the light
uniform mediump float pliw;     // 0 for directional, 1 for positional.
uniform mediump vec4 acm;       // Ambient color of the material
uniform mediump vec4 dcm;       // Diffuse color of the material
uniform mediump vec4 scm;       // Specular color of the material
uniform mediump float srm;      // Specular exponent of the material
uniform mediump vec4 acs;       // Light model's ambient color of the scene
uniform bool viewerAtInfinity;  // Light model indicates viewer at infinity

varying mediump vec4 qColor;
varying mediump vec4 qSecondaryColor;

void qLightVertex(vec4 vertex, vec3 normal)
{
    int i, material;
    vec3 toEye, toLight, h;
    float angle, spot, attenuation;
    vec4 color, scolor;
    vec4 adcomponent, scomponent;

    // Start with the material's emissive color and the ambient scene color.
    // ecm is assumed to be black.
    color = acm * acs;
    scolor = vec4(0, 0, 0, 0);

    // Vector from the vertex to the eye position (i.e. the origin).
    if (viewerAtInfinity)
        toEye = vec3(0, 0, 1);
    else
        toEye = normalize(-vertex.xyz);

    // Determine the cosine of the angle between the normal and the
    // vector from the vertex to the light.
    if (pliw == 0.0)
        toLight = normalize(pli);
    else
        toLight = normalize(pli - vertex.xyz);
    angle = max(dot(normal, toLight), 0.0);

    // Calculate the ambient and diffuse light components.
    // Assumptions: acli = (0, 0, 0, 1), dcli = (1, 1, 1, 1).
    adcomponent = acm * vec4(0, 0, 0, 1) + angle * dcm;

    // Calculate the specular light components.
    if (angle != 0.0) {
        h = normalize(toLight + toEye);
        angle = max(dot(normal, h), 0.0);
        scomponent = pow(angle, srm) * scm; // scli = (1, 1, 1, 1).
    } else {
        scomponent = vec4(0, 0, 0, 0);
    }

    // Add up the color components we computed.
    color += adcomponent;
    scolor += scomponent;

    // Generate the final output colors.
    float alpha = dcm.a;
    qColor = vec4(clamp(color.rgb, 0.0, 1.0), alpha);
    qSecondaryColor = clamp(scolor, 0.0, 1.0);
}

void main(void)
{
    gl_Position = matrix * vertex;
    highp vec4 vertex = modelView * vertex;
    highp vec3 norm = normalize(normalMatrix * normal);
    qLightVertex(vertex, norm);
    qTexCoord = texcoord;
}
